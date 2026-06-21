/*
 *  ObjectiveCObject.h
 *  objective-c-kit
 *
 *  Created by Fang Ling on 2026/4/18.
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

#import "ObjectiveCBase.h"

#ifdef __APPLE__
#  import <objc/NSObject.h>
#else
#  import "ObjFW/OFObject.h"
#endif

#import <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

@class FoundationString;

/**
 * The root class of most Objective-C class hierarchies, from which subclasses
 * inherit a basic interface to the runtime system and the ability to behave as
 * Objective-C objects.
 *
 * ## Topics
 *
 * ### Creating, Copying, and Deallocating Objects
 *
 * - ``alloc``
 * - ``init``
 * - ``dealloc``
 *
 * ### Testing Object Inheritance, Behavior, and Conformance
 *
 * - ``isKindOfClass:``
 */
@interface ObjectiveCObject
#ifdef __APPLE__
: NSObject
#else
: OFObject
#endif

/**
 * The class object.
 *
 * Refer to a class only by its name when it is the receiver of a message. In
 * all other cases, the class object must be obtained through this or a similar
 * method.
 */
@property (nonatomic, readonly, class) Class class;

/**
 * A textual representation of this instance.
 */
@property (nonatomic, readonly, copy) FoundationString* description;

/**
 * Returns a new instance of the receiving class.
 *
 * This is an instance variable of the new instance that is initialized to a
 * data structure describing the class; memory for all other instance variables
 * is set to 0.
 *
 * You must use an `init...` method to complete the initialization process. For
 * example:
 *
 * ```objective-c
 * var newObject = [[TheClass alloc] init];
 * ```
 *
 * Do not override ``alloc`` to include initialization code. Instead, implement
 * class-specific versions of `init...` methods.
 *
 * - Returns: A new instance of the receiver.
 */
+ (instancetype)alloc;

/**
 * Implemented by subclasses to initialize a new object (the receiver)
 * immediately after memory for it has been allocated.
 *
 * An `init` message is coupled with an `alloc` message in the same line of
 * code:
 *
 * ```objective-c
 * var object = [[SomeClass alloc] init];
 * ```
 *
 * An object isn't ready to be used until it has been initialized.
 *
 * In a custom implementation of this method, you must invoke super's `init`
 * then initialize and return the new object. If the new object can't be
 * initialized, the method should return `nil`. For example, a hypothetical
 * `BuiltInCamera` class might return `nil` from its `init` method if run on a
 * device that has no camera.
 *
 * ```objective-c
 * - (instancetype)init {
 *   if (self = [super init]) {
 *     // Initialize self here.
 *   }
 *   return self;
 * }
 * ```
 *
 * In some cases, a custom implementation of the ``init`` method might return a
 * substitute object. You must therefore always use the object returned by
 * ``init``, and not the one returned by ``alloc``, in subsequent code.
 *
 * The ``init`` method defined in the ``ObjectiveCObject`` class does no
 * initialization; it simply returns `self`. In terms of nullability, callers
 * can assume that the ``ObjectiveCObject`` implementation of ``init`` does not
 * return `nil`.
 *
 * - Returns: An initialized object, or `nil` if an object could not be created
 *   for some reason that would not result in an exception.
 */
- (instancetype)init
  OBJECTIVE_C_DESIGNATED_INITIALIZER;

/**
 * Deallocates the memory occupied by the receiver.
 *
 * Subsequent messages to the receiver may generate an error indicating that a
 * message was sent to a deallocated object (provided the deallocated memory
 * hasn't been reused yet).
 *
 * You override this method to dispose of resources other than the object's
 * instance variables, for example:
 *
 * ```objective-c
 * - (void)dealloc {
 *   free(myBigBlockOfMemory);
 * }
 * ```
 *
 * In an implementation of ``dealloc``, do not invoke the superclass's
 * implementation. You should try to avoid managing the lifetime of limited
 * resources such as file descriptors using ``dealloc``.
 *
 * You never send a ``dealloc`` message directly. Instead, an object's
 * ``dealloc`` method is invoked by the runtime.
 *
 * ### Special Considerations
 *
 * When not using ARC, your implementation of ``dealloc`` must invoke the
 * superclass's implementation as its last instruction.
 */
- (void)dealloc;

/**
 * Returns a Boolean value that indicates whether the receiver is an instance of
 * given class or an instance of any class that inherits from that class.
 *
 * Be careful when using this method on objects represented by a class cluster.
 * Because of the nature of class clusters, the object you get back may not
 * always be the type you expected. If you call a method that returns a class
 * cluster, the exact type returned by the method is the best indicator of what
 * you can do with that object. For example, if a method returns a pointer to an
 * ``FoundationArray`` object, you should not use this method to see if the
 * array is mutable, as shown in the following code:
 *
 *   ```objective-c
 *   // DO NOT DO THIS!
 *   if ([myArray isKindOfClass:FoundationMutableArray.class]) {
 *    // Modify the object
 *   }
 *   ```
 *
 * If you use such constructs in your code, you might think it is alright to
 * modify an object that in reality should not be modified. Doing so might then
 * create problems for other code that expected the object to remain unchanged.
 *
 * - Parameter class: A class object representing the Objective-C class to be
 *   tested.
 *
 * - Returns: `yes` if the receiver is an instance of the `class` or an instance
 *   of any class that inherits from `class`, otherwise `no`.
 */
- (CBoolean)isKindOfClass:(Class)class;

@end

C_ASSUME_NONNULL_END
