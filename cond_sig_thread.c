#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//       Compile and link with -pthread

// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

// Declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int done = 1;

void* create();

int main()
{
    pthread_t tid1, tid2;

    // Create thread 1
    pthread_create(&tid1, NULL, create, NULL);

    // Sleep for 1 sec so that thread 1
    // would get a chance to run first
    sleep(1);

    // Create thread 2
    pthread_create(&tid2, NULL, create, NULL);

    // Wait for the completion of thread 2
    pthread_join(tid2, NULL);

    return 0;
}

void *create()
{
    // Acquire a lock
    pthread_mutex_lock(&lock);

    if (done == 1)
    {
        done = 2;
        printf("Waiting on condition variable cond1\n");
        pthread_cond_wait(&cond1, &lock);
    }
    else
    {
        printf("Signaling condition variable cond1\n");
        pthread_cond_signal(&cond1);
    }

    // Release lock
    pthread_mutex_unlock(&lock);
    printf("Returning thread\n");

    return NULL;
}
