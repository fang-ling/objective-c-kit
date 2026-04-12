//
//  objfw.h
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

#include <stdint.h>

#include "../runtime_exports.h"

#pragma clang assume_nonnull begin

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sf_objfw_selector {
    const char *_Nullable name;
    const char *_Nullable types;
} SFObjFWSelector_t;

typedef struct sf_objfw_method {
    const char *_Nullable name;
    const char *_Nullable types;
    IMP _Nullable imp;
} SFObjFWMethod_t;

typedef struct SFObjFWMethodList {
    struct SFObjFWMethodList *_Nullable next;
    int32_t count;
    SFObjFWMethod_t methods[];
} SFObjFWMethodList_t;

typedef struct sf_objfw_ivar {
    const char *_Nullable name;
    const char *_Nullable type;
    int32_t offset;
} SFObjFWIvar_t;

typedef struct SFObjFWIvarList {
    int32_t count;
    SFObjFWIvar_t ivars[];
} SFObjFWIvarList_t;

typedef struct SFObjFWClass {
    struct SFObjFWClass *_Nullable isa;
    struct SFObjFWClass *_Nullable superclass;
    const char *_Nullable name;
    long version;
    unsigned long info;
    long instance_size;
    SFObjFWIvarList_t *_Nullable ivars;
    SFObjFWMethodList_t *_Nullable methods;
    void *_Nullable dtable;
    void *_Nullable subclass_list;
    void *_Nullable sibling_class;
    void *_Nullable protocols;
    void *_Nullable gc_object_type;
    unsigned long abi_version;
    int32_t *_Nullable *_Nullable ivar_offsets;
    void *_Nullable properties;
    unsigned long flags;
    unsigned long user_data;
} SFObjFWClass_t;

typedef struct SFObjFWSymtab {
    uintptr_t selector_count;
    SFObjFWSelector_t *_Nullable selectors;
    uint16_t class_count;
    uint16_t category_count;
    void *_Nullable definitions[];
} SFObjFWSymtab_t;

typedef struct SFObjFWModule {
    uintptr_t version;
    uintptr_t size;
    const char *_Nullable name;
    SFObjFWSymtab_t *_Nullable symtab;
    int32_t reserved;
} SFObjFWModule_t;

#ifdef __cplusplus
}
#endif

#pragma clang assume_nonnull end
