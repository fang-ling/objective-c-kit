//
//  c2x-compat.h
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

#if !defined(__cplusplus)
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L

#if !defined(alignas)
#define alignas _Alignas
#endif

#if !defined(alignof)
#define alignof _Alignof
#endif

#if !defined(static_assert)
#define static_assert _Static_assert
#endif

#if !defined(thread_local)
#define thread_local _Thread_local
#endif

#if !defined(nullptr)
#define nullptr 0
#endif

#endif

#if defined(__clang__) || defined(__GNUC__)
#if !defined(typeof)
#define typeof __typeof__
#endif
#endif

#if defined(__EMSCRIPTEN__) && !defined(__EMSCRIPTEN_PTHREADS__)
#if defined(thread_local)
#undef thread_local
#endif
#define thread_local
#endif
#endif
