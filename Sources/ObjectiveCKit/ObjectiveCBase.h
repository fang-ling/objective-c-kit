/*
 *  ObjectiveCBase.h
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

#ifndef ObjectiveCBase_h
#define ObjectiveCBase_h

#ifdef __APPLE__
#  import <objc/runtime.h>
#else
#  import "ObjFW/runtime/ObjFWRT.h"
#endif

#define OBJECTIVE_C_DESIGNATED_INITIALIZER \
  __attribute__((objc_designated_initializer))
#define OBJECTIVE_C_REQUIRES_NIL_TERMINATION __attribute__((sentinel(0,1)))

#define owning __strong
#define nonowning __weak

#define weakify(value) \
  autoreleasepool {} \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Wshadow\"") \
  __weak __typeof__(value) _weak_##value = value; \
  _Pragma("clang diagnostic pop")

#define strongify(value) \
  autoreleasepool {} \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Wshadow\"") \
  __strong __typeof__(_weak_##value) value = _weak_##value; \
  _Pragma("clang diagnostic pop")

#define bridging __bridge
#define retainedbridging __bridge_retained
#define transferredbridging __bridge_transfer

/**
 * A pointer to an instance of a class.
 */
typedef id ObjectiveCAnyObject;

/**
 * Returns the class definition of a specified class.
 *
 * - Parameter name: The name of the class to look up.
 *
 * - Returns The Class object for the named class, or `nil` if the class is not
 *   registered with the Objective-C runtime.
 */
#define ObjectiveCLookUpClass objc_lookUpClass

#endif /* ObjectiveCBase_h */
