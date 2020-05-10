#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#define NUM_BLOCKS 1000
/*
 * CSCE 4600 | Spring 2020 | Project #1
 * 		Filimon Gebrekidan
 * 		Luke Holman
 * 		Ethan Kolkmeier
 * 		Utsav Shrestha
 * 
 * For this project you will be working in groups of four. Each member of
 * your group must sign up on the corresponding project sheet in order to
 * receive a grade. Your task is to implement a semaphore-based solution to the
 * problem stated below.
 *
 * Consider a system with N blocks of storage, each of which holds one unit of
 * information (e.g. an integer, character, or employee record). Initially, these
 * blocks are empty and are linked onto a list called freelist. Three threads
 * communicate using shared memory/global variables in the following manner:
 *
 * Shared Variables: freelist, list-1, list-2: block
 *              (where block is some data type to hold items)
 * Thread-1
 * var b: pointer to type block; while (1) {
 *     b:= unlink(freelist); produce_information_in_block(b); link(b, list1);
 * }
 *
 * Thread-2
 * var x,y: pointer to type block; while (1) {
 *     x:=unlink(list-1); y:=unlink(freelist);
 *     use_block_x_to_produce info_in_y(x, y); link(x, freelist);
 *     link(y, list-2);
 * }
 * Thread-3
 * var c: pointer to type block; while(1) {
 *     c:=unlink(list-2); consume_information_in_block(c); link(c, freelist);
 * }
 *
 * Using the POSIX library, rewrite the code for the threads, using semaphores
 * to implement the necessary mutual exclusion and synchronization. The solution
 * must be deadlock-free and concurrency should not be unnecessarily restricted.
 *
 * */
static volatile int isRunning = 1;
sem_t mutex;

int getRand(int min, int max)
{
    return rand() % (max + 1 - min) + min;
}

void handler(int val)
{
    isRunning = 0;
}

typedef struct blocks
{
    int data;
    struct blocks *next;
} block;

block *freelist, *list_1, *list_2;

block *unlink(block **list)
{
    sem_wait(&mutex);
    if (list != NULL && *list != NULL)
    {
        block *head = *list;
        *list = (*list)->next;
        sem_post(&mutex);
        return head;
    }
    sem_post(&mutex);
    return NULL;
}

void link(block *node, block **head)
{
    if (node != NULL)
    {
        node->next = NULL;
        sem_wait(&mutex);
        if (*head != NULL)
        {
            node->next = *head;
            *head = node;
        } else
        {
            *head = node;
        }
        sem_post(&mutex);
    }
}

void produce_information_in_block(block *b)
{
    if (b != NULL)
        b->data = getRand(10, 100);
}

void consume_information_in_block(block *c)
{
    if (c != NULL)
        printf("Consuming info : %d\n", c->data);
}

void use_block_x_to_produce_info_in_y(block *x, block *y)
{
    if (x != NULL && y != NULL)
        y->data = x->data;
}

void *func1(void *arg)
{
    block *b;
    int k = 0;
    while (1)
    {
        b = unlink(&freelist);
        produce_information_in_block(b);
        link(b, &list_1);

        if (isRunning == 0)
            break;
    }
}

void *func2(void *arg)
{
    block *x, *y;
    while (1)
    {
        x = unlink(&list_1);
        y = unlink(&freelist);
        use_block_x_to_produce_info_in_y(x, y);
        link(x, &freelist);
        link(y, &list_2);

        if (isRunning == 0)
            break;
    }
}

void *func3(void *arg)
{
    block *c;
    while (1)
    {
        c = unlink(&list_2);
        consume_information_in_block(c);
        link(c, &freelist);

        if (isRunning == 0)
            break;
    }
}

void allocateBlocks()
{
    int i = 0;
    freelist = (block *) malloc(sizeof(block));
    freelist->next = NULL;
    block *curr = freelist;
    for (i = 1; i < NUM_BLOCKS; i++)
    {
        block *temp = (block *) malloc(sizeof(block));
        curr->next = temp;
        temp->next = NULL;
        curr = temp;
    }
}

void freeBlocks()
{
    int i = 0;
    block *curr = freelist;
    while (curr != NULL)
    {
        block *temp = curr;
        curr = curr->next;
        free(temp);
        i++;
    }

    curr = list_1;
    while (curr != NULL)
    {
        block *temp = curr;
        curr = curr->next;
        free(temp);
        i++;
    }

    curr = list_2;
    while (curr != NULL)
    {
        block *temp = curr;
        curr = curr->next;
        free(temp);
        i++;
    }

    printf("Total Deallocations: %d\n", i);
    printf("Expected Deallocations: %d\n", NUM_BLOCKS);

}

int main(int argc, char **argv)
{
    signal(SIGINT, handler);
    freelist = NULL;
    list_1 = NULL;
    list_2 = NULL;
    allocateBlocks();
    sem_init(&mutex, 0, 1);

    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    pthread_create(&thread1, NULL, func1, NULL);
    pthread_create(&thread2, NULL, func2, NULL);
    pthread_create(&thread3, NULL, func3, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    freeBlocks();

    sem_destroy(&mutex);

    return 0;
}

