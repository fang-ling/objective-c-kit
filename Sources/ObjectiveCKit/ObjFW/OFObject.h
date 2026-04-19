/*
 *  OFObject.h
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

#ifndef __STDC_LIMIT_MACROS
# define __STDC_LIMIT_MACROS
#endif
#ifndef __STDC_CONSTANT_MACROS
# define __STDC_CONSTANT_MACROS
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

#include "macros.h"

#import "OFOnce.h"

/*
 * Some versions of MinGW require <winsock2.h> to be included before
 * <windows.h>. Do this here to make sure this is always done in the correct
 * order, even if another header includes just <windows.h>.
 */
#ifdef __MINGW32__
# include <_mingw.h>
# ifdef __MINGW64_VERSION_MAJOR
#  include <winsock2.h>
#  include <windows.h>
# endif
#endif

OF_ASSUME_NONNULL_BEGIN

/** @file */

/**
 * @brief A special not found index.
 */
static const size_t OFNotFound = SIZE_MAX;

/**
 * @brief A result of a comparison.
 */
typedef enum {
	/** The left object is smaller than the right */
	OFOrderedAscending = -1,
	/** Both objects are equal */
	OFOrderedSame = 0,
	/** The left object is bigger than the right */
	OFOrderedDescending = 1
} OFComparisonResult;

/**
 * @brief A function to compare two objects.
 *
 * @param left The left object
 * @param right The right object
 * @param context Context passed along for comparing
 * @return The order of the objects
 */
typedef OFComparisonResult (*OFCompareFunction)(id _Nonnull left,
    id _Nonnull right, void *_Nullable context);

#ifdef OF_HAVE_BLOCKS
/**
 * @brief A comparator to compare two objects.
 *
 * @param left The left object
 * @param right The right object
 * @return The order of the objects
 */
typedef OFComparisonResult (^OFComparator)(id _Nonnull left, id _Nonnull right);
#endif

/**
 * @brief Adds the specified byte to the hash.
 *
 * @param hash A pointer to a hash to add the byte to
 * @param byte The byte to add to the hash
 */
static OF_INLINE void
OFHashAddByte(unsigned long *_Nonnull hash, unsigned char byte)
{
	uint32_t tmp = (uint32_t)*hash;

	tmp += byte;
	tmp += tmp << 10;
	tmp ^= tmp >> 6;

	*hash = tmp;
}

/**
 * @brief Adds the specified hash to the hash.
 *
 * @param hash A pointer to a hash to add the hash to
 * @param otherHash The hash to add to the hash
 */
static OF_INLINE void
OFHashAddHash(unsigned long *_Nonnull hash, unsigned long otherHash)
{
	OFHashAddByte(hash, (otherHash >> 24) & 0xFF);
	OFHashAddByte(hash, (otherHash >> 16) & 0xFF);
	OFHashAddByte(hash, (otherHash >>  8) & 0xFF);
	OFHashAddByte(hash, otherHash & 0xFF);
}

/**
 * @brief Finalizes the specified hash.
 *
 * @param hash A pointer to the hash to finalize
 */
static OF_INLINE void
OFHashFinalize(unsigned long *_Nonnull hash)
{
	uint32_t tmp = (uint32_t)*hash;

	tmp += tmp << 3;
	tmp ^= tmp >> 11;
	tmp += tmp << 15;

	*hash = tmp;
}

/**
 * @protocol OFObject OFObject.h ObjFW/ObjFW.h
 *
 * @brief The protocol which all root classes implement.
 */
@protocol OFObject
/**
 * @brief Returns the class of the object.
 *
 * @return The class of the object
 */
- (Class)class;

/**
 * @brief Returns the superclass of the object.
 *
 * @return The superclass of the object
 */
- (nullable Class)superclass;

/**
 * @brief Returns a hash for the object.
 *
 * Classes containing data (like strings, arrays, lists etc.) should reimplement
 * this!
 *
 * @warning If you reimplement this, you also need to reimplement @ref isEqual:
 *	    to behave in a way compatible to your reimplementation of this
 *	    method!
 *
 * @return A hash for the object
 */
- (unsigned long)hash;

/**
 * @brief Returns the retain count.
 *
 * @return The retain count
 */
- (unsigned int)retainCount;

/**
 * @brief Returns whether the object is a proxy object.
 *
 * @return Whether the object is a proxy object
 */
- (bool)isProxy;

/**
 * @brief Returns a boolean whether the object is of the specified kind.
 *
 * @param class_ The class for which the receiver is checked
 * @return A boolean whether the object is of the specified kind
 */
- (bool)isKindOfClass: (Class)class_;

/**
 * @brief Returns a boolean whether the object is a member of the specified
 *	  class.
 *
 * @param class_ The class for which the receiver is checked
 * @return A boolean whether the object is a member of the specified class
 */
- (bool)isMemberOfClass: (Class)class_;

/**
 * @brief Returns a boolean whether the object responds to the specified
 *	  selector.
 *
 * @param selector The selector which should be checked for respondence
 * @return A boolean whether the objects responds to the specified selector
 */
- (bool)respondsToSelector: (SEL)selector;

/**
 * @brief Checks whether the object conforms to the specified protocol.
 *
 * @param protocol The protocol which should be checked for conformance
 * @return A boolean whether the object conforms to the specified protocol
 */
- (bool)conformsToProtocol: (Protocol *)protocol;

/**
 * @brief Returns the implementation for the specified selector.
 *
 * @param selector The selector for which the method should be returned
 * @return The implementation for the specified selector
 */
- (nullable IMP)methodForSelector: (SEL)selector;

/**
 * @brief Performs the specified selector.
 *
 * @param selector The selector to perform
 * @return The object returned by the method specified by the selector
 */
- (nullable id)performSelector: (SEL)selector;

/**
 * @brief Performs the specified selector with the specified object.
 *
 * @param selector The selector to perform
 * @param object The object that is passed to the method specified by the
 *		 selector
 * @return The object returned by the method specified by the selector
 */
- (nullable id)performSelector: (SEL)selector withObject: (nullable id)object;

/**
 * @brief Performs the specified selector with the specified objects.
 *
 * @param selector The selector to perform
 * @param object1 The first object that is passed to the method specified by the
 *		  selector
 * @param object2 The second object that is passed to the method specified by
 *		  the selector
 * @return The object returned by the method specified by the selector
 */
- (nullable id)performSelector: (SEL)selector
		    withObject: (nullable id)object1
		    withObject: (nullable id)object2;

/**
 * @brief Performs the specified selector with the specified objects.
 *
 * @param selector The selector to perform
 * @param object1 The first object that is passed to the method specified by the
 *		  selector
 * @param object2 The second object that is passed to the method specified by
 *		  the selector
 * @param object3 The third object that is passed to the method specified by the
 *		  selector
 * @return The object returned by the method specified by the selector
 */
- (nullable id)performSelector: (SEL)selector
		    withObject: (nullable id)object1
		    withObject: (nullable id)object2
		    withObject: (nullable id)object3;

/**
 * @brief Performs the specified selector with the specified objects.
 *
 * @param selector The selector to perform
 * @param object1 The first object that is passed to the method specified by the
 *		  selector
 * @param object2 The second object that is passed to the method specified by
 *		  the selector
 * @param object3 The third object that is passed to the method specified by the
 *		  selector
 * @param object4 The fourth object that is passed to the method specified by
 *		  the selector
 * @return The object returned by the method specified by the selector
 */
- (nullable id)performSelector: (SEL)selector
		    withObject: (nullable id)object1
		    withObject: (nullable id)object2
		    withObject: (nullable id)object3
		    withObject: (nullable id)object4;

/**
 * @brief Checks two objects for equality.
 *
 * Classes containing data (like strings, arrays, lists etc.) should reimplement
 * this!
 *
 * @warning If you reimplement this, you also need to reimplement @ref hash to
 *	    return the same hash for objects which are equal!
 *
 * @param object The object which should be tested for equality
 * @return A boolean whether the object is equal to the specified object
 */
- (bool)isEqual: (nullable id)object;

/**
 * @brief Increases the retain count.
 *
 * Each time an object is released, the retain count gets decreased and the
 * object deallocated if it reaches 0.
 */
- (instancetype)retain;

/**
 * @brief Decreases the retain count.
 *
 * Each time an object is released, the retain count gets decreased and the
 * object deallocated if it reaches 0.
 */
- (void)release;

/**
 * @brief Adds the object to the topmost autorelease pool of the thread's
 *	  autorelease pool stack.
 *
 * @return The object
 */
- (instancetype)autorelease;

/**
 * @brief Returns the receiver.
 *
 * @return The receiver
 */
- (instancetype)self;

/**
 * @brief Returns whether the object allows a weak reference.
 *
 * @return Whether the object allows a weak references
 */
- (bool)allowsWeakReference;

/**
 * @brief Retain a weak reference to this object.
 *
 * @return Whether a weak reference to this object has been retained
 */
- (bool)retainWeakReference;
@end

/**
 * @class OFObject OFObject.h ObjFW/ObjFW.h
 *
 * @brief The root class for all other classes inside ObjFW.
 */
OF_ROOT_CLASS
@interface OFObject <OFObject>
{
@private
#ifndef __clang_analyzer__
	Class _isa;
#else
	Class _isa __attribute__((__unused__));
#endif
}

#ifdef OF_HAVE_CLASS_PROPERTIES
# ifndef __cplusplus
@property (class, readonly, nonatomic) Class class;
# else
@property (class, readonly, nonatomic, getter=class) Class class_;
# endif
@property (class, readonly, nullable, nonatomic) Class superclass;
#endif

#ifndef __cplusplus
@property (readonly, nonatomic) Class class;
#else
@property (readonly, nonatomic, getter=class) Class class_;
#endif
@property OF_NULLABLE_PROPERTY (readonly, nonatomic) Class superclass;
@property (readonly, nonatomic) unsigned long hash;
@property (readonly, nonatomic) unsigned int retainCount;
@property (readonly, nonatomic) bool isProxy;
@property (readonly, nonatomic) bool allowsWeakReference;

/**
 * @brief A method which is called once when the class is loaded into the
 *	  runtime.
 *
 * Derived classes can override this to execute their own code when the class
 * is loaded.
 *
 * @warning You cannot make use of other classes from inside this method! Only
 *	    the class itself, its superclasses and instances of the class or
 *	    its superclasses can be messaged!
 */
+ (void)load;

/**
 * @brief A method which is called when the class is unloaded from the runtime.
 *
 * Derived classes can override this to execute their own code when the class
 * is unloaded.
 *
 * @warning This is not supported by the Apple runtime and currently only
 *	    called by the ObjFW runtime when @ref objc_deinit has been called!
 *	    In the future, this might also be called by the ObjFW runtime when
 *	    the class is part of a plugin that is being unloaded.
 */
+ (void)unload;

/**
 * @brief A method which is called the moment before the first call to the class
 *	  is being made.
 *
 * Derived classes can override this to execute their own code on
 * initialization. They should make sure to not execute any code if self is not
 * the class itself, as it might happen that the method was called for a
 * subclass which did not override this method.
 */
+ (void)initialize;

/**
 * @brief Allocates memory for an instance of the class and sets up the memory
 *	  pool for the object.
 *
 * This method will never return `nil`.
 *
 * @return The allocated object
 * @throw OFAllocFailedException There was not enough memory to allocate the
 *				 object
 * @throw OFInitializationFailedException The instance could not be constructed
 */
+ (instancetype)alloc;

/**
 * @brief Returns the class.
 *
 * @return The class
 */
+ (Class)class;

/**
 * @brief Returns a boolean whether the class is a subclass of the specified
 *	  class.
 *
 * @param class_ The class which is checked for being a superclass
 * @return A boolean whether the class is a subclass of the specified class
 */
+ (bool)isSubclassOfClass: (Class)class_;

/**
 * @brief Returns the superclass of the class.
 *
 * @return The superclass of the class
 */
+ (nullable Class)superclass;

/**
 * @brief Checks whether instances of the class respond to a given selector.
 *
 * @param selector The selector which should be checked for respondence
 * @return A boolean whether instances of the class respond to the specified
 *	   selector
 */
+ (bool)instancesRespondToSelector: (SEL)selector;

/**
 * @brief Checks whether the class conforms to a given protocol.
 *
 * @param protocol The protocol which should be checked for conformance
 * @return A boolean whether the class conforms to the specified protocol
 */
+ (bool)conformsToProtocol: (Protocol *)protocol;

/**
 * @brief Returns the implementation of the instance method for the specified
 *	  selector.
 *
 * @param selector The selector for which the method should be returned
 * @return The implementation of the instance method for the specified selector
 *	   or `nil` if it isn't implemented
 */
+ (nullable IMP)instanceMethodForSelector: (SEL)selector;

/**
 * @brief Try to resolve the specified class method.
 *
 * This method is called if a class method was not found, so that an
 * implementation can be provided at runtime.
 *
 * @return Whether the method has been added to the class
 */
+ (bool)resolveClassMethod: (SEL)selector;

/**
 * @brief Try to resolve the specified instance method.
 *
 * This method is called if an instance method was not found, so that an
 * implementation can be provided at runtime.
 *
 * @return Whether the method has been added to the class
 */
+ (bool)resolveInstanceMethod: (SEL)selector;

/**
 * @brief Returns the class.
 *
 * This method exists so that classes can be used in collections requiring
 * conformance to the OFCopying protocol.
 *
 * @return The class of the object
 */
+ (id)copy;

/**
 * @brief Initializes an already allocated object.
 *
 * Derived classes may override this, but need to use the following pattern:
 * @code
 * self = [super init];
 *
 * @try {
 *         // Custom initialization code goes here.
 * } @catch (id e) {
 *         objc_release(self);
 *         @throw e;
 * }
 *
 * return self;
 * @endcode
 *
 * With ARC enabled, the following pattern needs to be used instead:
 * @code
 * self = [super init];
 *
 * // Custom initialization code goes here.
 *
 * return self;
 * @endcode
 *
 * @ref init may never return `nil`, instead an exception (for example
 * @ref OFInitializationFailedException) should be thrown.
 *
 * @return An initialized object
 */
- (instancetype)init;

/**
 * @brief Deallocates the object.
 *
 * It is automatically called when the retain count reaches zero.
 *
 * This also frees all memory in its memory pool.
 */
- (void)dealloc;

/**
 * @brief This method is called when @ref resolveClassMethod: or
 *	  @ref resolveInstanceMethod: returned false. It should return a target
 *	  to which the message should be forwarded.
 *
 * @note When the message should not be forwarded, you should not return `nil`,
 *	 but instead return the result of `[super
 *	 forwardingTargetForSelector: selector]`.
 *
 * @return The target to forward the message to
 */
- (nullable id)forwardingTargetForSelector: (SEL)selector;

@end

/**
 * @protocol OFCopying OFObject.h ObjFW/ObjFW.h
 *
 * @brief A protocol for the creation of copies.
 */
@protocol OFCopying
/**
 * @brief Copies the object.
 *
 * For classes which can be immutable or mutable, this returns an immutable
 * copy. If only a mutable version of the class exists, it creates a mutable
 * copy.
 *
 * @return A copy of the object
 */
- (id)copy;
@end

/**
 * @protocol OFMutableCopying OFObject.h ObjFW/ObjFW.h
 *
 * @brief A protocol for the creation of mutable copies.
 *
 * This protocol is implemented by objects that can be mutable and immutable
 * and allows returning a mutable copy.
 */
@protocol OFMutableCopying
/**
 * @brief Creates a mutable copy of the object.
 *
 * @return A mutable copy of the object
 */
- (id)mutableCopy;
@end

/**
 * @protocol OFComparing OFObject.h ObjFW/ObjFW.h
 *
 * @brief A protocol for comparing objects.
 *
 * This protocol is implemented by objects that can be compared. Its only
 * method, @ref compare:, should be overridden with a stronger type.
 */
@protocol OFComparing
/**
 * @brief Compares the object to another object.
 *
 * @param object An object to compare the object to
 * @return The result of the comparison
 */
- (OFComparisonResult)compare: (id <OFComparing>)object;
@end

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Allocates memory for the specified number of items of the specified
 *	  size.
 *
 * To free the allocated memory, use @ref OFFreeMemory.
 *
 * @param count The number of items to allocate
 * @param size The size of each item to allocate
 * @return A pointer to the allocated memory. May return NULL if the specified
 *	   size or count is 0.
 * @throw OFOutOfMemoryException The allocation failed due to not enough memory
 * @throw OFOutOfRangeException The requested `count * size` exceeds the
 *				address space
 */
extern void *_Nullable OFAllocMemory(size_t count, size_t size)
    OF_MALLOC_FUNC OF_WARN_UNUSED_RESULT;

/**
 * @brief Allocates memory for the specified number of items of the specified
 *	  size and initializes it with zeros.
 *
 * To free the allocated memory, use @ref OFFreeMemory.
 *
 * @param size The size of each item to allocate
 * @param count The number of items to allocate
 * @return A pointer to the allocated memory. May return NULL if the specified
 *	   size or count is 0.
 * @throw OFOutOfMemoryException The allocation failed due to not enough memory
 * @throw OFOutOfRangeException The requested `count * size` exceeds the
 *				address space
 */
extern void *_Nullable OFAllocZeroedMemory(size_t count, size_t size)
    OF_MALLOC_FUNC OF_WARN_UNUSED_RESULT;

/**
 * @brief Resizes memory to the specified number of items of the specified size.
 *
 * To free the allocated memory, use @ref OFFreeMemory.
 *
 * If the pointer is NULL, this is equivalent to allocating memory.
 * If the size or number of items is 0, this is equivalent to freeing memory.
 *
 * @param pointer A pointer to the already allocated memory
 * @param size The size of each item to resize to
 * @param count The number of items to resize to
 * @return A pointer to the resized memory chunk
 * @throw OFOutOfMemoryException The reallocation failed due to not enough
 *				 memory
 * @throw OFOutOfRangeException The requested `count * size` exceeds the
 *				address space
 */
extern void *_Nullable OFResizeMemory(void *_Nullable pointer, size_t count,
    size_t size) OF_WARN_UNUSED_RESULT;

/**
 * @brief Frees memory allocated by @ref OFAllocMemory, @ref OFAllocZeroedMemory
 *	  or @ref OFResizeMemory.
 *
 * @param pointer A pointer to the memory to free or nil (passing nil does
 *		  nothing)
 */
extern void OFFreeMemory(void *_Nullable pointer);

/**
 * @brief Allocates a new object.
 *
 * This is useful to override @ref OFObject#alloc in a subclass that can then
 * allocate extra memory in the same memory allocation.
 *
 * @param class_ The class of which to allocate an object
 * @param extraSize Extra space after the ivars to allocate
 * @param extraAlignment Alignment of the extra space after the ivars
 * @param extra A pointer to set to a pointer to the extra space
 * @return The allocated object
 */
extern id OFAllocObject(Class class_, size_t extraSize, size_t extraAlignment,
    void *_Nullable *_Nullable extra);

/**
 * @brief This function is called when a method is not found.
 *
 * It can also be called intentionally to indicate that a method is not
 * implemented, for example in an abstract method. However, instead of calling
 * OFMethodNotFound directly, it is preferred to do the following:
 *
 *     - (void)abstractMethod
 *     {
 *             OF_UNRECOGNIZED_SELECTOR
 *     }
 *
 * However, do not use this for init methods. Instead, use the following:
 *
 *     - (instancetype)init
 *     {
 *             OF_INVALID_INIT_METHOD
 *     }
 *
 * @param self The object which does not have the method
 * @param _cmd The selector of the method that does not exist
 */
extern void OF_NO_RETURN_FUNC OFMethodNotFound(id self, SEL _cmd);

#ifdef __cplusplus
}
#endif

OF_ASSUME_NONNULL_END

#import "OFBlock.h"

#endif /* !__APPLE__ */
