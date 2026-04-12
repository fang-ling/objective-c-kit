//
//  common.h
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

#include "../internal.h"

#pragma clang assume_nonnull begin

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SFObjCAliasEntry {
    const char *alias_name;
    Class _Nullable *_Nullable class_ref;
} SFObjCAliasEntry_t;

SEL _Nullable sf_loader_intern_selector_name_types(const char *_Nullable name, const char *_Nullable types);
void sf_loader_register_selector_region(void *_Nullable start, void *_Nullable stop);
void sf_loader_register_class_aliases(SFObjCAliasEntry_t *_Nullable start, SFObjCAliasEntry_t *_Nullable stop);
SFObjCClass_t *_Nullable sf_loader_class_lookup_unlocked(const char *_Nullable name);
int sf_loader_local_ivar_offset_unlocked(SFObjCClass_t *cls, size_t index, int32_t *offset_out);
void sf_loader_sync_ivar_offset_unlocked(SFObjCClass_t *cls, size_t index, int32_t offset);
void sf_loader_prepare_registered_classes_unlocked(void);

#ifdef __cplusplus
}
#endif

#pragma clang assume_nonnull end
