//
//  InvalidArgumentException.m
//  objective-c-kit
//
//  Derived from SmallFW by Fang Ling on 2026/4/12.
//
//  Copyright 2026 Amrit Bhogal
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include "Object.h"

#include <stdlib.h>

#include "abi.h"
#include "internal.h"

typedef struct SFStaticInvalidArgumentException {
    SFObjHeader_t hdr;
    Class isa;
} SFStaticInvalidArgumentException_t;

@implementation InvalidArgumentException

+ (instancetype)exception
{
    static thread_local SFStaticInvalidArgumentException_t fallback;

    id exc = sf_alloc_object((Class)self, sf_default_allocator());
    if (exc != nullptr) {
      return [(InvalidArgumentException *)exc initialize];
    }

    exc = [self allocInPlace:&fallback size:sizeof(fallback)];
    if (exc != nullptr) {
      return [(InvalidArgumentException *)exc initialize];
    }
    return nullptr;
}

@end
