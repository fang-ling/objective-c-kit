//
//  sf_allocator.h
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

#pragma once

#include <stddef.h>

#pragma clang assume_nonnull begin

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SFAllocator {
    void *_Nullable (*_Nonnull alloc)(void *_Nullable ctx, size_t size, size_t align);
    void (*_Nonnull free)(void *_Nullable ctx, void *_Nullable ptr, size_t size, size_t align);
    void *_Nullable ctx;
} SFAllocator_t;

SFAllocator_t *sf_default_allocator(void);

#ifdef __cplusplus
}
#endif

#pragma clang assume_nonnull end
