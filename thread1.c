#include <pthread.h>
#include <stdio.h>

// A thread can be seen as a lightweight process
// A process may have multiple threads but threads can only belong to one process
// Requires -pthread flag on compilation

void *update_value(void *arg);

int main()
{
    int i, *ret, value[10];
    pthread_t thread_id[10];

    for (i = 0; i < 10; i++)
    {
        value[i] = i;

        // int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        //                   void *(*start_routine) (void *), void *arg);

        // The pthread_create() function starts a new thread in the calling process.
        // The new thread starts execution by invoking start_routine(); arg is passed
        // as the sole argument of start_routine().
        pthread_create(&thread_id[i], NULL, update_value, (void *) &value[i]);
    }

    for (i = 0; i < 10; i++)
    {
        // int pthread_join(pthread_t thread, void **retval);

        // The pthread_join() function waits for the thread specified by thread
        //       to terminate.  If that thread has already terminated, then
        //       pthread_join() returns immediately.  The thread specified by thread
        //       must be joinable.
        //
        //       If retval is not NULL, then pthread_join() copies the exit status of
        //       the target thread (i.e., the value that the target thread supplied to
        //       pthread_exit(3)) into the location pointed to by retval.  If the
        //       target thread was canceled, then PTHREAD_CANCELED is placed in the
        //       location pointed to by retval.
        //
        //       If multiple threads simultaneously try to join with the same thread,
        //       the results are undefined.  If the thread calling pthread_join() is
        //       canceled, then the target thread will remain joinable (i.e., it will
        //       not be detached).
        pthread_join(thread_id[i], (void **) &ret);
        printf("Thread %d: %d %d \n", i, value[i], *ret);
    }

    return 0;
}

void *update_value(void *arg)
{
    int i, *count;
    count = (int *) arg;

    for (i = 0; i < 10; i++)
        *count += 1;

    // The pthread_exit() function terminates the calling thread and returns
    //       a value via retval that (if the thread is joinable) is available to
    //       another thread in the same process that calls pthread_join(3).
    //
    //       Any clean-up handlers established by pthread_cleanup_push(3) that
    //       have not yet been popped, are popped (in the reverse of the order in
    //       which they were pushed) and executed.  If the thread has any thread-
    //       specific data, then, after the clean-up handlers have been executed,
    //       the corresponding destructor functions are called, in an unspecified
    //       order.
    //
    //       When a thread terminates, process-shared resources (e.g., mutexes,
    //       condition variables, semaphores, and file descriptors) are not
    //       released, and functions registered using atexit(3) are not called.
    //
    //       After the last thread in a process terminates, the process terminates
    //       as by calling exit(3) with an exit status of zero; thus, process-
    //       shared resources are released and functions registered using
    //       atexit(3) are called.
    pthread_exit(count);
}

