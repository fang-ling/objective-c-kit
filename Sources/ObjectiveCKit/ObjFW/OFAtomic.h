/*
 *  OFAtomic.h
 *  objective-c-kit
 *
 *  Derived from ObjFW by Fang Ling on 2026/4/18.
 *
 *  Copyright (c) 2008-2026 Jonathan Schleifer <js@nil.im>
 *
 *  All rights reserved.
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

#ifndef __APPLE__

#include <stdlib.h>

#import "macros.h"

#if (defined(OF_AMD64) || defined(OF_X86)) && defined(__GNUC__)
# import "platform/x86/OFAtomic.h"
#elif defined(OF_POWERPC) && defined(__GNUC__) && !defined(__APPLE_CC__) && \
    !defined(OF_AIX)
# import "platform/PowerPC/OFAtomic.h"
#elif defined(OF_ARM64) || defined(__wasi__)
# import "platform/GCC4.7/OFAtomic.h"
#else
# error No atomic operations available!
#endif

#endif /* !__APPLE__ */
