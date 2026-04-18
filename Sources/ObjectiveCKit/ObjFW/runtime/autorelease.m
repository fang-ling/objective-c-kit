/*
 *  autorelease.m
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

#include <stdio.h>
#include <stdlib.h>

#import "ObjFWRT.h"
#import "private.h"

#import "macros.h"

#if defined(OF_HAVE_COMPILER_TLS)
static thread_local id *objects = NULL;
static thread_local uintptr_t count = 0;
static thread_local uintptr_t size = 0;
#endif

void *
objc_autoreleasePoolPush(void)
{
	return (void *)count;
}

void
objc_autoreleasePoolPop(void *pool)
{
	uintptr_t idx = (uintptr_t)pool;
	bool freeMem = false;

	if (idx == (uintptr_t)-1) {
		idx++;
		freeMem = true;
	}

	for (uintptr_t i = idx; i < count; i++) {
		objc_release(objects[i]);
	}

	count = idx;

	if (freeMem) {
		free(objects);
		objects = NULL;
#if defined(OF_HAVE_COMPILER_TLS)
		size = 0;
#endif
	}
}

id
_objc_rootAutorelease(id object)
{
	if (count >= size) {
		if (size == 0)
			size = 16;
		else
			size *= 2;

		if ((objects = realloc(objects, size * sizeof(id))) == NULL)
			_OBJC_ERROR("Failed to resize autorelease pool!");
	}

	objects[count++] = object;

	return object;
}

#endif /* !__APPLE__ */
