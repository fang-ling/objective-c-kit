/*
 *  association.m
 *  objective-c-kit
 *
 *  Derived from ObjFW by Fang Ling on 2026/4/18.
 *
 *  Copyright (c) 2008-2026 Jonathan Schleifer <js@nil.im>
 *
 *  All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU Lesser General Public License version 3.0 only,
 *  as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 *  version 3.0 for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  version 3.0 along with this program. If not, see
 *  <https://www.gnu.org/licenses/>.
 */

#ifndef __APPLE__

#import "ObjFWRT.h"
#import "private.h"

#import "pre_ivar.h"

#import "OFAtomic.h"

struct Association {
	id object;
	objc_associationPolicy policy;
};

typedef struct objc_hashtable _objc_hashtable;

/* Inlined and unnecessary checks dropped for performance. */
static OF_INLINE Class
_object_getClass_fast(id object_)
{
	struct objc_object *object = (struct objc_object *)object_;

	return object->isa;
}

#define numSlots 16	/* needs to be a power of 2 */
#import "OFPlainMutex.h"
static OFSpinlock spinlocks[numSlots];
static _objc_hashtable *hashtables[numSlots];

static OF_INLINE size_t
slotForObject(id object)
{
	return ((size_t)((uintptr_t)object >> 4) & (numSlots - 1));
}

static uint32_t
hash(const void *object)
{
	return (uint32_t)(uintptr_t)object;
}

static bool
equal(const void *object1, const void *object2)
{
	return (object1 == object2);
}

OF_CONSTRUCTOR()
{
	for (size_t i = 0; i < numSlots; i++) {
		hashtables[i] = _objc_hashtable_new(hash, equal, 2);

		if (OFSpinlockNew(&spinlocks[i]) != 0)
			_OBJC_ERROR("Failed to create spinlocks!");
	}
}

void
objc_setAssociatedObject(id object, const void *key, id value,
    objc_associationPolicy policy)
{
	size_t slot;

	switch (policy) {
	case OBJC_ASSOCIATION_ASSIGN:
		break;
	case OBJC_ASSOCIATION_RETAIN:
	case OBJC_ASSOCIATION_RETAIN_NONATOMIC:
		value = objc_retain(value);
		break;
	case OBJC_ASSOCIATION_COPY:
	case OBJC_ASSOCIATION_COPY_NONATOMIC:
		value = [value copy];
		break;
	default:
		/* Don't know what to do, so do nothing. */
		return;
	}

	if (!object_isTaggedPointer(object) &&
	    (_object_getClass_fast(object)->info & _OBJC_CLASS_INFO_RUNTIME_RR))
		OFAtomicIntOr(&_OBJC_PRE_IVARS(object)->info,
		    _OBJC_OBJECT_INFO_ASSOCIATIONS);

	slot = slotForObject(object);

	if (OFSpinlockLock(&spinlocks[slot]) != 0)
		_OBJC_ERROR("Failed to lock spinlock!");

		_objc_hashtable *objectHashtable;
		struct Association *association;

		objectHashtable = _objc_hashtable_get(hashtables[slot], object);
		if (objectHashtable == NULL) {
			objectHashtable = _objc_hashtable_new(hash, equal, 2);
			_objc_hashtable_set(hashtables[slot], object,
			    objectHashtable);
		}

		association = _objc_hashtable_get(objectHashtable, key);
		if (association != NULL) {
			switch (association->policy) {
			case OBJC_ASSOCIATION_RETAIN:
			case OBJC_ASSOCIATION_RETAIN_NONATOMIC:
			case OBJC_ASSOCIATION_COPY:
			case OBJC_ASSOCIATION_COPY_NONATOMIC:
				objc_release(association->object);
				break;
			default:
				break;
			}
		} else {
			association = malloc(sizeof(*association));
			if (association == NULL)
				_OBJC_ERROR("Failed to allocate association!");

			_objc_hashtable_set(objectHashtable, key, association);
		}

		association->policy = policy;
		association->object = value;

		if (OFSpinlockUnlock(&spinlocks[slot]) != 0)
			_OBJC_ERROR("Failed to unlock spinlock!");
}

id
objc_getAssociatedObject(id object, const void *key)
{
	size_t slot = slotForObject(object);
	id ret = nil;

	if (OFSpinlockLock(&spinlocks[slot]) != 0)
		_OBJC_ERROR("Failed to lock spinlock!");

		_objc_hashtable *objectHashtable;
		struct Association *association;

		objectHashtable = _objc_hashtable_get(hashtables[slot], object);
  if (objectHashtable == NULL) {

    if (OFSpinlockUnlock(&spinlocks[slot]) != 0)
      _OBJC_ERROR("Failed to unlock spinlock!");

    return nil;
  }

		association = _objc_hashtable_get(objectHashtable, key);
  if (association == NULL) {

    if (OFSpinlockUnlock(&spinlocks[slot]) != 0)
      _OBJC_ERROR("Failed to unlock spinlock!");

    return nil;
  }

		switch (association->policy) {
		case OBJC_ASSOCIATION_RETAIN:
		case OBJC_ASSOCIATION_COPY:
			ret = objc_autoreleaseReturnValue(
			    objc_retain(association->object));
			break;
		default:
			ret = association->object;
			break;
		}

		if (OFSpinlockUnlock(&spinlocks[slot]) != 0)
			_OBJC_ERROR("Failed to unlock spinlock!");

	return ret;
}

void
objc_removeAssociatedObjects(id object)
{
	size_t slot;

	OFReleaseMemoryBarrier();

	if (object != nil && !object_isTaggedPointer(object) &&
	    (_object_getClass_fast(object)->info &
	    _OBJC_CLASS_INFO_RUNTIME_RR) && !(_OBJC_PRE_IVARS(object)->info &
	    _OBJC_OBJECT_INFO_ASSOCIATIONS))
		return;

	slot = slotForObject(object);

	if (OFSpinlockLock(&spinlocks[slot]) != 0)
		_OBJC_ERROR("Failed to lock spinlock!");

		_objc_hashtable *objectHashtable;

		objectHashtable = _objc_hashtable_get(hashtables[slot], object);
		if (objectHashtable == NULL)
			return;

		for (uint32_t i = 0; i < objectHashtable->size; i++) {
			struct Association *association;

			if (objectHashtable->data[i] == NULL ||
			    objectHashtable->data[i] == &_objc_deletedBucket)
				continue;

			association = (struct Association *)
			    objectHashtable->data[i]->object;

			switch (association->policy) {
			case OBJC_ASSOCIATION_RETAIN:
			case OBJC_ASSOCIATION_RETAIN_NONATOMIC:
			case OBJC_ASSOCIATION_COPY:
			case OBJC_ASSOCIATION_COPY_NONATOMIC:
				objc_release(association->object);
				break;
			default:
				break;
			}

			free(association);
		}

		_objc_hashtable_delete(hashtables[slot], object);
		_objc_hashtable_free(objectHashtable);

		if (OFSpinlockUnlock(&spinlocks[slot]) != 0)
			_OBJC_ERROR("Failed to unlock spinlock!");
}

#endif /* !__APPLE__ */
