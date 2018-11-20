#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

int counter;
pthread_t thread_id[2];
pthread_mutex_t lock;

void *report()
{
    // int pthread_mutex_lock(pthread_mutex_t *mutex);

    //       The mutex object referenced by mutex shall be locked by a call to
    //       pthread_mutex_lock() that returns zero or [EOWNERDEAD].  If the mutex
    //       is already locked by another thread, the calling thread shall block
    //       until the mutex becomes available. This operation shall return with
    //       the mutex object referenced by mutex in the locked state with the
    //       calling thread as its owner. If a thread attempts to relock a mutex
    //       that it has already locked, pthread_mutex_lock() shall behave as
    //       described in the Relock column of the following table. If a thread
    //       attempts to unlock a mutex that it has not locked or a mutex which is
    //       unlocked, pthread_mutex_unlock() shall behave as described in the
    //       Unlock When Not Owner column of the following table.
    //
    //        ┌───────────┬────────────┬────────────────┬───────────────────────┐
    //        │Mutex Type │ Robustness │     Relock     │ Unlock When Not Owner │
    //        ├───────────┼────────────┼────────────────┼───────────────────────┤
    //        │NORMAL     │ non-robust │ deadlock       │ undefined behavior    │
    //        ├───────────┼────────────┼────────────────┼───────────────────────┤
    //        │NORMAL     │ robust     │ deadlock       │ error returned        │
    //        ├───────────┼────────────┼────────────────┼───────────────────────┤
    //        │ERRORCHECK │ either     │ error returned │ error returned        │
    //        ├───────────┼────────────┼────────────────┼───────────────────────┤
    //        │RECURSIVE  │ either     │ recursive      │ error returned        │
    //        │           │            │ (see below)    │                       │
    //        ├───────────┼────────────┼────────────────┼───────────────────────┤
    //        │DEFAULT    │ non-robust │ undefined      │ undefined behavior†   │
    //        │           │            │ behavior†      │                       │
    //        ├───────────┼────────────┼────────────────┼───────────────────────┤
    //        │DEFAULT    │ robust     │ undefined      │ error returned        │
    //        │           │            │ behavior†      │                       │
    //        └───────────┴────────────┴────────────────┴───────────────────────┘
    //       †     If the mutex type is PTHREAD_MUTEX_DEFAULT, the behavior of
    //             pthread_mutex_lock() may correspond to one of the three other
    //             standard mutex types as described in the table above. If it
    //             does not correspond to one of those three, the behavior is
    //             undefined for the cases marked †.
    //
    //       Where the table indicates recursive behavior, the mutex shall
    //       maintain the concept of a lock count. When a thread successfully
    //       acquires a mutex for the first time, the lock count shall be set to
    //       one. Every time a thread relocks this mutex, the lock count shall be
    //       incremented by one. Each time the thread unlocks the mutex, the lock
    //       count shall be decremented by one. When the lock count reaches zero,
    //       the mutex shall become available for other threads to acquire.
	pthread_mutex_lock(&lock);

	unsigned long i = 0;
	counter += 1;
	printf("\n Job %d has started\n", counter);

	for(i = 0; i < (0xFFFFFFFF); i++);

	printf("\n Job %d has finished\n", counter);

	  //       The pthread_mutex_trylock() function shall be equivalent to
    //       pthread_mutex_lock(), except that if the mutex object referenced by
    //       mutex is currently locked (by any thread, including the current
    //       thread), the call shall return immediately. If the mutex type is
    //       PTHREAD_MUTEX_RECURSIVE and the mutex is currently owned by the
    //       calling thread, the mutex lock count shall be incremented by one and
    //       the pthread_mutex_trylock() function shall immediately return
    //       success.
    //
    //       The pthread_mutex_unlock() function shall release the mutex object
    //       referenced by mutex.  The manner in which a mutex is released is
    //       dependent upon the mutex's type attribute. If there are threads
    //       blocked on the mutex object referenced by mutex when
    //       pthread_mutex_unlock() is called, resulting in the mutex becoming
    //       available, the scheduling policy shall determine which thread shall
    //       acquire the mutex.
    //
    //       (In the case of PTHREAD_MUTEX_RECURSIVE mutexes, the mutex shall
    //       become available when the count reaches zero and the calling thread
    //       no longer has any locks on this mutex.)
    //
    //       If a signal is delivered to a thread waiting for a mutex, upon return
    //       from the signal handler the thread shall resume waiting for the mutex
    //       as if it was not interrupted.
    //
    //       If mutex is a robust mutex and the process containing the owning
    //       thread terminated while holding the mutex lock, a call to
    //       pthread_mutex_lock() shall return the error value [EOWNERDEAD].  If
    //       mutex is a robust mutex and the owning thread terminated while
    //       holding the mutex lock, a call to pthread_mutex_lock() may return the
    //       error value [EOWNERDEAD] even if the process in which the owning
    //       thread resides has not terminated. In these cases, the mutex is
    //       locked by the thread but the state it protects is marked as
    //       inconsistent. The application should ensure that the state is made
    //       consistent for reuse and when that is complete call
    //       pthread_mutex_consistent().  If the application is unable to recover
    //       the state, it should unlock the mutex without a prior call to
    //       pthread_mutex_consistent(), after which the mutex is marked
    //       permanently unusable.
    //
    //       If mutex does not refer to an initialized mutex object, the behavior
    //       of pthread_mutex_lock(), pthread_mutex_trylock(), and
    //       pthread_mutex_unlock() is undefined.
    //
    // RETURN VALUE
    //
    //       If successful, the pthread_mutex_lock(), pthread_mutex_trylock(), and
    //       pthread_mutex_unlock() functions shall return zero; otherwise, an
    //       error number shall be returned to indicate the error.
	pthread_mutex_unlock(&lock);

	return NULL;
}

int main(void)
{
	int i = 0, error;

	// int pthread_mutex_init( pthread_mutex_t* mutex,
    //                         const pthread_mutexattr_t* attr );

    // The pthread_mutex_init() function initializes the given mutex object,
    // using the attributes specified by the mutex attributes object attr.
    // If attr is NULL, then the mutex is initialized with the default attributes
    // After initialization, the mutex is in an unlocked state.
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("\n mutex init has failed\n");
		return 1;
	}

	while (i < 2)
	{
		error = pthread_create(&thread_id[i], NULL, &report, NULL);
		if (error != 0)
			printf("\nThread can't be created :[%s]", strerror(error));

		i++;
	}

	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);
	
	pthread_mutex_destroy(&lock);

	return 0;
}

