typedef struct _rwlock_t {
    sem_t writelock;
    sem_t lock;
    int   readers;
} rwlock_t;

void rwlock_init(rwlock_t *lock) {
    readers = 0;
    sem_init(&lock, 0, 1);      // binary semaphore
    sem_init(&writelock, 0, 1); // used to lock out a writer, or all readers
}

void rwlock_acquire_readlock(rwlock_t *lock) {
    sem_wait(&lock);
    readers++;
    if (readers == 1)
        sem_wait(&writelock);
    sem_post(&lock);
}

void rwlock_release_readlock(rwlock_t *lock) {
    sem_wait(&lock);
    readers--;
    if (readers == 0)
        sem_post(&writelock);
    sem_post(&lock);
}

void rwlock_acquire_writelock(rwlock_t *lock) {
    sem_wait(&writelock);
}

void rwlock_release_writelock(rwlock_t *lock) {
    sem_post(&writelock);
}
