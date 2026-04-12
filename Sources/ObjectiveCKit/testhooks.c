//
//  testhooks.c
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

#include "internal.h"

#include <stdlib.h>

static size_t g_test_alloc_fail_after = SIZE_MAX;

int sf_runtime_test_consume_allocation(void)
{
    if (g_test_alloc_fail_after == SIZE_MAX) {
        return 1;
    }
    if (g_test_alloc_fail_after == 0) {
        g_test_alloc_fail_after = SIZE_MAX;
        return 0;
    }
    g_test_alloc_fail_after -= 1;
    return 1;
}

void sf_runtime_test_reset_alloc_failures(void)
{
    g_test_alloc_fail_after = SIZE_MAX;
}

void sf_runtime_test_fail_allocation_after(size_t successful_allocations)
{
    g_test_alloc_fail_after = successful_allocations;
}

void *sf_runtime_test_malloc(size_t size)
{
    if (not sf_runtime_test_consume_allocation()) {
        return nullptr;
    }
    return malloc(size);
}

void *sf_runtime_test_calloc(size_t count, size_t size)
{
    if (not sf_runtime_test_consume_allocation()) {
        return nullptr;
    }
    return calloc(count, size);
}

void *sf_runtime_test_realloc(void *ptr, size_t size)
{
    if (not sf_runtime_test_consume_allocation()) {
        return nullptr;
    }
    return realloc(ptr, size);
}
