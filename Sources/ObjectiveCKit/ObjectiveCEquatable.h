/*
 *  ObjectiveCEquatable.h
 *  objective-c-kit
 *
 *  Created by Fang Ling on 2026/6/6.
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

#import <CKit/CKit.h>

C_ASSUME_NONNULL_BEGIN

/**
 * A type that can be compared for value equality.
 *
 * Types that conform to the ``ObjectiveCEquatable`` protocol can be compared
 * for equality or inequality using the `isEqual:` method. Most basic types
 * conform to ``ObjectiveCEquatable``.
 */
@protocol ObjectiveCEquatable

/**
 * Returns a Boolean value that indicates whether the receiver and a given
 * object are equal.
 *
 * This method defines what it means for instances to be equal. For example, a
 * container object might define two containers as equal if their corresponding
 * objects all respond `yes` to an `isEqual:` request.
 *
 * - Parameter object: The object to be compared to the receiver. May be `nil`,
 *   in which case this method returns `no`.
 *
 * - Returns: `yes` if the receiver and the `object` are equal, otherwise `no`.
 */
- (CBoolean)isEqual:(nullable ObjectiveCAnyObject)object;

@end

C_ASSUME_NONNULL_END
