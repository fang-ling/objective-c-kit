/*
 *  OFPlainMutex.h
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

#include <errno.h>

#include "platform.h"

#import "macros.h"

/** @file */

#include <pthread.h>
typedef pthread_mutex_t OFPlainMutex;

#import "OFAtomic.h"
typedef volatile int OFSpinlock;

#include <sched.h>

#define OFPlainRecursiveMutex OFPlainMutex

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Creates a new plain mutex.
 *
 * A plain mutex is similar to an @ref OFMutex, but does not use exceptions and
 * is just a lightweight wrapper around the system's mutex implementation.
 *
 * @param mutex A pointer to the mutex to create
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainMutexNew(OFPlainMutex *mutex);

/**
 * @brief Locks the specified mutex.
 *
 * @param mutex A pointer to the mutex to lock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainMutexLock(OFPlainMutex *mutex);

/**
 * @brief Tries to lock the specified mutex without blocking.
 *
 * @param mutex A pointer to the mutex to try to lock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainMutexTryLock(OFPlainMutex *mutex);

/**
 * @brief Unlocks the specified mutex.
 *
 * @param mutex A pointer to the mutex to unlock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainMutexUnlock(OFPlainMutex *mutex);

/**
 * @brief Destroys the specified mutex
 *
 * @param mutex A pointer to the mutex to destruct
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainMutexFree(OFPlainMutex *mutex);

/**
 * @brief Creates a new plain recursive mutex.
 *
 * A plain recursive mutex is similar to an @ref OFRecursiveMutex, but does not
 * use exceptions and is just a lightweight wrapper around the system's
 * recursive mutex implementation (or lacking that, a simple implementation of
 * recursive mutexes via regular mutexes).
 *
 * @param rmutex A pointer to the recursive mutex to create
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainRecursiveMutexNew(OFPlainRecursiveMutex *rmutex);

/**
 * @brief Locks the specified recursive mutex.
 *
 * @param rmutex A pointer to the recursive mutex to lock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainRecursiveMutexLock(OFPlainRecursiveMutex *rmutex);

/**
 * @brief Tries to lock the specified recursive mutex without blocking.
 *
 * @param rmutex A pointer to the recursive mutex to try to lock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainRecursiveMutexTryLock(OFPlainRecursiveMutex *rmutex);

/**
 * @brief Unlocks the specified recursive mutex.
 *
 * @param rmutex A pointer to the recursive mutex to unlock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainRecursiveMutexUnlock(OFPlainRecursiveMutex *rmutex);

/**
 * @brief Destroys the specified recursive mutex
 *
 * @param rmutex A pointer to the recursive mutex to destruct
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
extern int OFPlainRecursiveMutexFree(OFPlainRecursiveMutex *rmutex);
#ifdef __cplusplus
}
#endif

/* Spinlocks are inlined for performance. */

/**
 * @brief Yield the current thread, indicating to the OS that another thread
 *	  should execute instead.
 */
static OF_INLINE void
OFYieldThread(void)
{
	sched_yield();
}

/**
 * @brief Creates a new spinlock.
 *
 * @param spinlock A pointer to the spinlock to create
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
static OF_INLINE int
OFSpinlockNew(OFSpinlock *spinlock)
{
	*spinlock = 0;
	return 0;
}

/**
 * @brief Tries to lock a spinlock.
 *
 * @param spinlock A pointer to the spinlock to try to lock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
static OF_INLINE int
OFSpinlockTryLock(OFSpinlock *spinlock)
{
	if (OFAtomicIntCompareAndSwap(spinlock, 0, 1)) {
		OFAcquireMemoryBarrier();
		return 0;
	}

	return EBUSY;
}

/**
 * @brief Locks a spinlock.
 *
 * @param spinlock A pointer to the spinlock to lock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
static OF_INLINE int
OFSpinlockLock(OFSpinlock *spinlock)
{
	size_t i;

	for (i = 0; i < 10; i++)
		if (OFSpinlockTryLock(spinlock) == 0)
			return 0;

	while (OFSpinlockTryLock(spinlock) == EBUSY)
		OFYieldThread();

	return 0;
}

/**
 * @brief Unlocks a spinlock.
 *
 * @param spinlock A pointer to the spinlock to unlock
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
static OF_INLINE int
OFSpinlockUnlock(OFSpinlock *spinlock)
{
	bool ret = OFAtomicIntCompareAndSwap(spinlock, 1, 0);

	OFReleaseMemoryBarrier();

	return (ret ? 0 : EINVAL);
}

/**
 * @brief Destroys a spinlock.
 *
 * @param spinlock A pointer to the spinlock to destroy
 * @return 0 on success, or an error number from `<errno.h>` on error
 */
static OF_INLINE int
OFSpinlockFree(OFSpinlock *spinlock)
{
	(void)spinlock;

	return 0;
}

#endif /* !__APPLE__ */
