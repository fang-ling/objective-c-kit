/*
 *  ObjectiveCObject.m
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

#import "ObjectiveCObject.h"

C_ASSUME_NONNULL_BEGIN

@implementation ObjectiveCObject

+ (instancetype)alloc {
  return [super alloc];
}

+ (Class)class {
  return super.class;
}

- (instancetype)init {
  return [super init];
}

- (FoundationString*)description {
  CDebuggingHaltWithMessage(
    "*** ABSTRACT METHOD description IS BEING CALLED. ***"
  );
}

- (void)dealloc {
  [super dealloc];
}

- (CBoolean)isKindOfClass:(Class)class {
  return [super isKindOfClass:class];
}

/* MARK: - ObjectiveCObject Implementations */
- (CBoolean)respondsToSelector:(ObjectiveCSelector)selector {
  return [super respondsToSelector:selector];
}

@end

C_ASSUME_NONNULL_END
