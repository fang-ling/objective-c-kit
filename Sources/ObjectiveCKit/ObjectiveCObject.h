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

#import "Base.h"

#ifdef __APPLE__
#  import <objc/NSObject.h>
#else
#  import "ObjFW/OFObject.h"
#endif

OBJECTIVE_C_ASSUME_NONNULL_BEGIN

#ifdef __APPLE__
@interface ObjectiveCObject: NSObject
#else
@interface ObjectiveCObject: OFObject
#endif

@end

OBJECTIVE_C_ASSUME_NONNULL_END
