#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Define the read-write lock structure
typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t readers_cond;
    pthread_cond_t writer_cond;
    int readers;
    int writer;
} rwlock_t;

rwlock_t rw_lock;

// Initialize the read-write lock
void rwlock_init(rwlock_t *lock) {
    pthread_mutex_init(&lock->mutex, NULL);
    pthread_cond_init(&lock->readers_cond, NULL);
    pthread_cond_init(&lock->writer_cond, NULL);
    lock->readers = 0;
    lock->writer = 0;
}

// Acquire the read lock
void rwlock_readlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    while (lock->writer > 0) {
        pthread_cond_wait(&lock->readers_cond, &lock->mutex);
    }
    lock->readers++;
    pthread_mutex_unlock(&lock->mutex);
}

// Release the read lock
void rwlock_readunlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    lock->readers--;
    if (lock->readers == 0) {
        pthread_cond_signal(&lock->writer_cond);
    }
    pthread_mutex_unlock(&lock->mutex);
}

// Acquire the write lock
void rwlock_writelock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    while (lock->readers > 0 || lock->writer > 0) {
        pthread_cond_wait(&lock->writer_cond, &lock->mutex);
    }
    lock->writer = 1;
    pthread_mutex_unlock(&lock->mutex);
}

// Release the write lock
void rwlock_writeunlock(rwlock_t *lock) {
    pthread_mutex_lock(&lock->mutex);
    lock->writer = 0;
    pthread_cond_broadcast(&lock->readers_cond);
    pthread_cond_signal(&lock->writer_cond);
    pthread_mutex_unlock(&lock->mutex);
}

// Reader thread function
void *readlockThread(void *arg) {
    printf("Entered thread, getting read lock\n");
    rwlock_readlock(&rw_lock);
    printf("got the rwlock read lock\n");

    sleep(5);

    printf("unlock the read lock\n");
    rwlock_readunlock(&rw_lock);
    printf("Secondary thread unlocked\n");
    return NULL;
}

// Writer thread function
void *writelockThread(void *arg) {
    printf("Entered thread, getting write lock\n");
    rwlock_writelock(&rw_lock);

    printf("Got the rwlock write lock, now unlock\n");
    rwlock_writeunlock(&rw_lock);
    printf("Secondary thread unlocked\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    printf("Main, initialize the read write lock\n");
    rwlock_init(&rw_lock);

    printf("Main, grab a read lock\n");
    rwlock_readlock(&rw_lock);

    printf("Main, grab the same read lock again\n");
    rwlock_readlock(&rw_lock);

    printf("Main, create the read lock thread\n");
    pthread_create(&thread1, NULL, readlockThread, NULL);

    sleep(1);  // Ensure the thread starts before unlocking
    printf("Main - unlock the first read lock\n");
    rwlock_readunlock(&rw_lock);

    printf("Main, create the write lock thread\n");
    pthread_create(&thread2, NULL, writelockThread, NULL);

    sleep(5);
    printf("Main - unlock the second read lock\n");
    rwlock_readunlock(&rw_lock);

    printf("Main, wait for the threads\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Main completed\n");

    return 0;
}
