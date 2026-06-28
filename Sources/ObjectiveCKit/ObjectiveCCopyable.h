/*
 *  ObjectiveCCopyable.h
 *  objective-c-kit
 *
 *  Created by Fang Ling on 2026/6/28.
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
 * A protocol that objects adopt to provide functional copies of themselves.
 *
 * The exact meaning of "copy" can vary from class to class, but a copy must be
 * a functionally independent object with values identical to the original at
 * the time the copy was made. A copy produced with ``ObjectiveCCopyable`` is
 * implicitly retained by the sender, who is responsible for releasing it.
 */
@protocol ObjectiveCCopyable

/**
 * Returns a new instance that's a copy of the receiver.
 *
 * The returned object is implicitly retained by the sender, who is responsible
 * for releasing it. The copy returned is immutable if the consideration
 * "immutable vs. mutable" applies to the receiving object; otherwise the exact
 * nature of the copy is determined by the class.
 *
 * - Returns: A new instance that's a copy of the receiver.
 */
- (ObjectiveCAnyObject)copy;

@end

C_ASSUME_NONNULL_END
