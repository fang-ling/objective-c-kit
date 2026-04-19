/*
 *  OFObject.m
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unistd_wrapper.h"

#import "OFObject.h"

#import "ObjFWRT.h"

#ifdef OF_WINDOWS
# include <windows.h>
#endif

#ifdef OF_AMIGAOS
# define Class IntuitionClass
# define USE_INLINE_STDARG
# include <proto/exec.h>
# include <clib/debug_protos.h>
# define __NOLIBBASE_
# include <proto/intuition.h>
# undef __NOLIBBASE_
# undef Class
#endif

#if defined(OF_HAVE_FORWARDING_TARGET_FOR_SELECTOR)
extern id _OFForward(id, SEL, ...);
extern struct Stret _OFForward_stret(id, SEL, ...);
#else
# define _OFForward OFMethodNotFound
# define _OFForward_stret OFMethodNotFound_stret
#endif

#ifdef OF_WINDOWS
static BOOLEAN NTAPI (*RtlGenRandomFuncPtr)(PVOID, ULONG);
#endif

static struct {
	Class isa;
} allocFailedException;

static const char *
typeEncodingForSelector(Class class, SEL selector)
{
	Method method;

	if ((method = class_getInstanceMethod(class, selector)) == NULL)
		return NULL;

	return method_getTypeEncoding(method);
}

void OF_NO_RETURN_FUNC
OFMethodNotFound(id object, SEL selector)
{
	/*
	 * Just in case doesNotRecognizeSelector: returned, even though it must
	 * never return.
	 */
	abort();

	OF_UNREACHABLE
}

void OF_NO_RETURN_FUNC
OFMethodNotFound_stret(void *stret, id object, SEL selector)
{
	OFMethodNotFound(object, selector);
}

@implementation OFObject
+ (void)load
{
	objc_setForwardHandler((IMP)&_OFForward, (IMP)&_OFForward_stret);

	objc_setTaggedPointerSecret(sizeof(uintptr_t) == 4
	    ? (uintptr_t)arc4random():((uintptr_t)arc4random() << 32) | arc4random());
}

+ (void)unload
{
}

+ (void)initialize
{
}

+ (instancetype)alloc
{
	OFObject *instance = class_createInstance(self, 0);

	return instance;
}

+ (Class)class
{
	return self;
}

+ (bool)isSubclassOfClass: (Class)class
{
	for (Class iter = self; iter != Nil; iter = class_getSuperclass(iter))
		if (iter == class)
			return true;

	return false;
}

+ (Class)superclass
{
	return class_getSuperclass(self);
}

+ (bool)instancesRespondToSelector: (SEL)selector
{
	return class_respondsToSelector(self, selector);
}

+ (bool)conformsToProtocol: (Protocol *)protocol
{
	for (Class iter = self; iter != Nil; iter = class_getSuperclass(iter))
		if (class_conformsToProtocol(iter, protocol))
			return true;

	return false;
}

+ (IMP)instanceMethodForSelector: (SEL)selector
{
	return class_getMethodImplementation(self, selector);
}

+ (bool)resolveClassMethod: (SEL)selector
{
	return false;
}

+ (bool)resolveInstanceMethod: (SEL)selector
{
	return false;
}

- (instancetype)init
{
	return self;
}

- (Class)class
{
	return object_getClass(self);
}

- (Class)superclass
{
	return class_getSuperclass(object_getClass(self));
}

- (bool)isKindOfClass: (Class)class
{
	for (Class iter = object_getClass(self); iter != Nil;
	    iter = class_getSuperclass(iter))
		if (iter == class)
			return true;

	return false;
}

- (bool)isMemberOfClass: (Class)class
{
	return (object_getClass(self) == class);
}

- (bool)respondsToSelector: (SEL)selector
{
	return class_respondsToSelector(object_getClass(self), selector);
}

- (bool)conformsToProtocol: (Protocol *)protocol
{
	return [object_getClass(self) conformsToProtocol: protocol];
}

- (IMP)methodForSelector: (SEL)selector
{
	return class_getMethodImplementation(object_getClass(self), selector);
}

- (id)performSelector: (SEL)selector
{
	id (*imp)(id, SEL) = (id (*)(id, SEL))objc_msg_lookup(self, selector);

	return imp(self, selector);
}

- (id)performSelector: (SEL)selector withObject: (id)object
{
	id (*imp)(id, SEL, id) =
	    (id (*)(id, SEL, id))objc_msg_lookup(self, selector);

	return imp(self, selector, object);
}

- (id)performSelector: (SEL)selector
	   withObject: (id)object1
	   withObject: (id)object2
{
	id (*imp)(id, SEL, id, id) =
	    (id (*)(id, SEL, id, id))objc_msg_lookup(self, selector);

	return imp(self, selector, object1, object2);
}

- (id)performSelector: (SEL)selector
	   withObject: (id)object1
	   withObject: (id)object2
	   withObject: (id)object3
{
	id (*imp)(id, SEL, id, id, id) =
	    (id (*)(id, SEL, id, id, id))objc_msg_lookup(self, selector);

	return imp(self, selector, object1, object2, object3);
}

- (id)performSelector: (SEL)selector
	   withObject: (id)object1
	   withObject: (id)object2
	   withObject: (id)object3
	   withObject: (id)object4
{
	id (*imp)(id, SEL, id, id, id, id) =
	    (id (*)(id, SEL, id, id, id, id))objc_msg_lookup(self, selector);

	return imp(self, selector, object1, object2, object3, object4);
}

- (bool)isEqual: (id)object
{
	return (object == self);
}

- (id)forwardingTargetForSelector: (SEL)selector
{
	return nil;
}

- (void)_usesRuntimeRR
{
}

- (instancetype)retain
{
	return _objc_rootRetain(self);
}

- (unsigned int)retainCount
{
	return (unsigned int)_objc_rootRetainCount(self);
}

- (void)release
{
	_objc_rootRelease(self);
}

- (instancetype)autorelease
{
	return _objc_rootAutorelease(self);
}

- (instancetype)self
{
	return self;
}

- (bool)isProxy
{
	return false;
}

- (bool)allowsWeakReference
{
	return true;
}

- (bool)retainWeakReference
{
	[self retain];

	return true;
}

- (void)dealloc
{
	object_dispose(self);
}

/* Required to use properties with the Apple runtime */
- (id)copyWithZone: (void *)zone
{
	if OF_UNLIKELY (zone != NULL) {
		abort();
	}

	return [(id)self copy];
}

- (id)mutableCopyWithZone: (void *)zone
{
	if OF_UNLIKELY (zone != NULL) {
		abort();
	}

	return [(id)self mutableCopy];
}

/*
 * The following are needed as the root class is the superclass of the root
 * class's metaclass and thus instance methods can be sent to class objects as
 * well.
 */

+ (id)retain
{
	return self;
}

+ (id)autorelease
{
	return self;
}

+ (unsigned int)retainCount
{
	return OFMaxRetainCount;
}

+ (void)release
{
}

+ (void)dealloc
{
	OF_UNRECOGNIZED_SELECTOR
}

+ (id)copy
{
	return self;
}

+ (id)mutableCopyWithZone: (void *)zone
{
	OF_UNRECOGNIZED_SELECTOR
}

/* Required to use ObjFW from Swift */
+ (instancetype)allocWithZone: (void *)zone
{
	if OF_UNLIKELY (zone != NULL) {
		abort();
	}

	return [self alloc];
}
@end

#endif /* !__APPLE__ */
