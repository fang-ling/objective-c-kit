/*
 *  OFPlainMutex.m
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

#import "OFPlainMutex.h"

int
OFPlainMutexNew(OFPlainMutex *mutex)
{
	return pthread_mutex_init(mutex, NULL);
}

int
OFPlainMutexLock(OFPlainMutex *mutex)
{
	return pthread_mutex_lock(mutex);
}

int
OFPlainMutexTryLock(OFPlainMutex *mutex)
{
	return pthread_mutex_trylock(mutex);
}

int
OFPlainMutexUnlock(OFPlainMutex *mutex)
{
	return pthread_mutex_unlock(mutex);
}

int
OFPlainMutexFree(OFPlainMutex *mutex)
{
	return pthread_mutex_destroy(mutex);
}

int
OFPlainRecursiveMutexNew(OFPlainRecursiveMutex *rmutex)
{
	int error;
	pthread_mutexattr_t attr;

	if ((error = pthread_mutexattr_init(&attr)) != 0)
		return error;

	if ((error = pthread_mutexattr_settype(&attr,
	    PTHREAD_MUTEX_RECURSIVE)) != 0)
		return error;

	if ((error = pthread_mutex_init(rmutex, &attr)) != 0)
		return error;

	if ((error = pthread_mutexattr_destroy(&attr)) != 0)
		return error;

	return 0;
}

int
OFPlainRecursiveMutexLock(OFPlainRecursiveMutex *rmutex)
{
	return OFPlainMutexLock(rmutex);
}

int
OFPlainRecursiveMutexTryLock(OFPlainRecursiveMutex *rmutex)
{
	return OFPlainMutexTryLock(rmutex);
}

int
OFPlainRecursiveMutexUnlock(OFPlainRecursiveMutex *rmutex)
{
	return OFPlainMutexUnlock(rmutex);
}

int
OFPlainRecursiveMutexFree(OFPlainRecursiveMutex *rmutex)
{
	return OFPlainMutexFree(rmutex);
}

#endif /* !__APPLE__ */
