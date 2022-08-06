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

pthread_mutex_t mutex;
sem_t wrt;
int cnt=1, numreader=0;

void * writer(void *wno) {
    sem_wait(&wrt);
    cnt = cnt*2;
    printf("\nWriter %d: Changed cnt to %d\n", *((int *)wno) ,cnt);
    sem_post(&wrt);
}

void * reader(void *rno) {
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);
    printf("\nReader %d: Read cnt as %d\n", *((int *)rno), cnt);
    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
}

void main() {
    pthread_t read[10], write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int i=0; i<10; i++) 
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    for(int i=0; i<5; i++) 
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    for(int i=0; i<10; i++) 
        pthread_join(read[i], NULL);
    for(int i=0; i<5; i++) 
        pthread_join(write[i], NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return;
}
