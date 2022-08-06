/***********************************************************************************************************************************************************************
 * Program to implement the procducer consumer problem, using semaphores.
 * The pthread_mutex_init() function shall initialize the mutex referenced by mutex with attributes specified by attr.  
 * If attr is NULL, the default mutex attributes are used
 * Prototype: int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
 * The mutex object referenced by mutex shall be locked by a call to pthread_mutex_lock().
 * Prototype: int pthread_mutex_lock(pthread_mutex_t *mutex);
 * The pthread_mutex_unlock() function shall release the mutex object referenced by mutex.
 * Prototype: int pthread_mutex_unlock(pthread_mutex_t *mutex);
 * The pthread_mutex_destroy() function shall destroy the mutex object referenced by mutex.
 * Prototype:  int pthread_mutex_destroy(pthread_mutex_t *mutex);
 * The pthread_create() function starts a new thread in the calling process.
 * Prototype: int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
 * The pthread_join() function waits for the thread specified by thread to terminate.
 * Prototype: int pthread_join(pthread_t thread, void **retval);
 * The sem_init() function initializes the unnamed semaphore at the address pointed to by sem.
 * Prototype: int sem_init(sem_t *sem, int pshared, unsigned int value);
 * The sem_wait() function decrements (locks) the semaphore pointed to by sem.
 * Prototype: int sem_wait(sem_t *sem);
 * The sem_post() function increments (unlocks) the semaphore pointed to by sem.
 * Prototype: int sem_post(sem_t *sem);
 * The sem_destroy() function destroys the unnamed semaphore at the address pointed to by sem.
 * Prototype: int sem_destroy(sem_t *sem);
***********************************************************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MAXITEMS 5
#define BUFFER_SIZE 5

pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int in =0, out = 0, buffer[BUFFER_SIZE];

void * producer(void *pno) {
    int item;
    for(int i=0; i<MAXITEMS; i++) {
        item = rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("\nProducer %d: Insered item %d at %d\n", *((int *)pno), item, in);
        in = (in+1)%BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void * consumer(void *cno) {
    int item;
    for(int i=0; i<MAXITEMS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("\nConsumer %d: Removed item %d from %d\n", *((int *)cno), item, out);
        out = (out+1)%BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void main() {
    pthread_t pro[5], con[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    int a[] = {1, 2, 3, 4, 5};
    for(int i=0; i<5; i++)
        pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);
    for(int i=0; i<5; i++)
        pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);
    for(int i=0; i<5; i++)
        pthread_join(pro[i], NULL);
    for(int i=0; i<5; i++)
        pthread_join(con[i], NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return;
}