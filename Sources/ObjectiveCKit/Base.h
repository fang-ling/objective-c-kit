/*
 *  Base.h
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

#ifndef Base_h
#define Base_h

#import <stdbool.h>
#import <stdint.h>

#define OBJECTIVE_C_ASSUME_NONNULL_BEGIN _Pragma("clang assume_nonnull begin")
#define OBJECTIVE_C_ASSUME_NONNULL_END   _Pragma("clang assume_nonnull end")

#define OBJECTIVE_C_DESIGNATED_INITIALIZER \
  __attribute__((objc_designated_initializer))
#define OBJECTIVE_C_REQUIRES_NIL_TERMINATION __attribute__((sentinel(0,1)))

#define owning __strong
#define nonowning __weak
#define var __auto_type
#define NONNULL _Nonnull
#define NULLABLE _Nullable

/**
 * A value type whose instances are either `true` or `false`.
 *
 * It's recommended to use only simple Boolean values in conditional contexts to
 * help avoid accidental programming errors and to help maintain the clarity of
 * each control statement.
 */
typedef bool ObjectiveCBoolean;

/**
 * A 32-bit signed integer value type.
 */
typedef int32_t ObjectiveCInteger32;

/**
 * A 32-bit unsigned integer value type.
 */
typedef uint32_t ObjectiveCUnsignedInteger32;

/**
 * A 64-bit signed integer value type.
 */
typedef int64_t ObjectiveCInteger64;

/**
 * A 64-bit unsigned integer value type.
 */
typedef uint64_t ObjectiveCUnsignedInteger64;


#endif /* Base_h */
