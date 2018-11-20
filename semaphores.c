#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//       Compile and link with -pthread

sem_t mutex;

void *thread();

int main()
{
    // int sem_init(sem_t *sem, int pshared, unsigned int value);

    //       sem_init() initializes the unnamed semaphore at the address pointed
    //       to by sem.  The value argument specifies the initial value for the
    //       semaphore.
    //
    //       The pshared argument indicates whether this semaphore is to be shared
    //       between the threads of a process, or between processes.
    //
    //       If pshared has the value 0, then the semaphore is shared between the
    //       threads of a process, and should be located at some address that is
    //       visible to all threads (e.g., a global variable, or a variable
    //       allocated dynamically on the heap).
    //
    //       If pshared is nonzero, then the semaphore is shared between
    //       processes, and should be located in a region of shared memory (see
    //       shm_open(3), mmap(2), and shmget(2)).  (Since a child created by
    //       fork(2) inherits its parent's memory mappings, it can also access the
    //       semaphore.)  Any process that can access the shared memory region can
    //       operate on the semaphore using sem_post(3), sem_wait(3), and so on.
    //
    //       Initializing a semaphore that has already been initialized results in
    //       undefined behavior.
    sem_init(&mutex, 0, 1);

    pthread_t thread1,thread2;
    pthread_create(&thread1,NULL,thread,NULL);

    sleep(2);

    pthread_create(&thread2,NULL,thread,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    // int sem_destroy(sem_t *sem);

    //       sem_destroy() destroys the unnamed semaphore at the address pointed
    //       to by sem.
    //
    //       Only a semaphore that has been initialized by sem_init(3) should be
    //       destroyed using sem_destroy().
    //
    //       Destroying a semaphore that other processes or threads are currently
    //       blocked on (in sem_wait(3)) produces undefined behavior.
    //
    //       Using a semaphore that has been destroyed produces undefined results,
    //       until the semaphore has been reinitialized using sem_init(3).
    sem_destroy(&mutex);

    return 0;
}

void *thread()
{
    // int sem_wait(sem_t *sem);

    //       sem_wait() decrements (locks) the semaphore pointed to by sem.  If
    //       the semaphore's value is greater than zero, then the decrement
    //       proceeds, and the function returns, immediately.  If the semaphore
    //       currently has the value zero, then the call blocks until either it
    //       becomes possible to perform the decrement (i.e., the semaphore value
    //       rises above zero), or a signal handler interrupts the call.
    //
    //       sem_trywait() is the same as sem_wait(), except that if the decrement
    //       cannot be immediately performed, then call returns an error (errno
    //       set to EAGAIN) instead of blocking.
    //
    //       sem_timedwait() is the same as sem_wait(), except that abs_timeout
    //       specifies a limit on the amount of time that the call should block if
    //       the decrement cannot be immediately performed.  The abs_timeout
    //       argument points to a structure that specifies an absolute timeout in
    //       seconds and nanoseconds since the Epoch, 1970-01-01 00:00:00 +0000
    //       (UTC).  This structure is defined as follows:
    //
    //           struct timespec {
    //               time_t tv_sec;      /* Seconds */
    //               long   tv_nsec;     /* Nanoseconds [0 .. 999999999] */
    //           };
    //
    //       If the timeout has already expired by the time of the call, and the
    //       semaphore could not be locked immediately, then sem_timedwait() fails
    //       with a timeout error (errno set to ETIMEDOUT).
    //
    //       If the operation can be performed immediately, then sem_timedwait()
    //       never fails with a timeout error, regardless of the value of
    //       abs_timeout.  Furthermore, the validity of abs_timeout is not checked
    //       in this case.
    sem_wait(&mutex);
    printf("\nEntered..\n");

    sleep(4);

    printf("\nJust Exiting...\n");

    // int sem_post(sem_t *sem);

    //       sem_post() increments (unlocks) the semaphore pointed to by sem.  If
    //       the semaphore's value consequently becomes greater than zero, then
    //       another process or thread blocked in a sem_wait(3) call will be woken
    //       up and proceed to lock the semaphore.
    sem_post(&mutex);
}

