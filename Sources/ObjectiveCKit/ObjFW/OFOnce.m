/*
 *  OFOnce.m
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

#include <stdbool.h>

#import "OFOnce.h"
#import "OFAtomic.h"
#import "OFPlainMutex.h"

#ifdef OF_AMIGAOS
# define Class IntuitionClass
# include <proto/exec.h>
# undef Class
#endif

void
OFOnce(OFOnceControl *control, void (*function)(void))
{
	pthread_once(control, function);
}

#endif /* !__APPLE__ */
