#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

//       Compile and link with -pthread

pthread_t thread_id[2];
int count;

void *report()
{
    unsigned long i = 0;
    count += 1;
    printf("\n Job %d has started\n", count);

    // The two's-complement system has the advantage of not
    // requiring that the addition and subtraction circuitry
    // examine the signs of the operands to determine whether
    // to add or subtract. This property makes the system
    // both simpler to implement and capable of easily handling
    // higher precision arithmetic.
    for (i = 0; i < (0xFFFFFFFF); i++);
    printf("\n Job %d has finished\n", count);

    return NULL;
}

int main(void)
{
    int i = 0;
    int error;

    while (i < 2)
    {
        // int pthread_create(pthread_t *thread,
        //                    const pthread_attr_t *attr,
        //                    void *(*start_routine) (void *),
        //                    void *arg);

        // The pthread_create() function starts a new thread in the calling
        //       process.  The new thread starts execution by invoking
        //       start_routine(); arg is passed as the sole argument of
        //       start_routine().
        //
        //       The new thread terminates in one of the following ways:
        //
        //       * It calls pthread_exit(3), specifying an exit status value that is
        //         available to another thread in the same process that calls
        //         pthread_join(3).
        //
        //       * It returns from start_routine().  This is equivalent to calling
        //         pthread_exit(3) with the value supplied in the return statement.
        //
        //       * It is canceled (see pthread_cancel(3)).
        //
        //       * Any of the threads in the process calls exit(3), or the main thread
        //         performs a return from main().  This causes the termination of all
        //         threads in the process.
        //
        //       The attr argument points to a pthread_attr_t structure whose contents
        //       are used at thread creation time to determine attributes for the new
        //       thread; this structure is initialized using pthread_attr_init(3) and
        //       related functions.  If attr is NULL, then the thread is created with
        //       default attributes.
        //
        //       Before returning, a successful call to pthread_create() stores the ID
        //       of the new thread in the buffer pointed to by thread; this identifier
        //       is used to refer to the thread in subsequent calls to other pthreads
        //       functions.
        //
        //       The new thread inherits a copy of the creating thread's signal mask
        //       (pthread_sigmask(3)).  The set of pending signals for the new thread
        //       is empty (sigpending(2)).  The new thread does not inherit the
        //       creating thread's alternate signal stack (sigaltstack(2)).
        //
        //       The new thread inherits the calling thread's floating-point
        //       environment (fenv(3)).
        //
        //       The initial value of the new thread's CPU-time clock is 0 (see
        //       pthread_getcpuclockid(3)).
        error = pthread_create(&thread_id[i], NULL, &report, NULL);
        if (error != 0)
            printf("\nThread can't be created: %s", strerror(error));

        i++;
    }

    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);

    return 0;
}

