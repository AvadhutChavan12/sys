#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

int data = 0, readers = 0;
pthread_mutex_t mutexLock;
pthread_mutex_t writeLock;

void* readerSync(void*) {
    pthread_mutex_lock(&mutexLock);
    readers++;
    if (readers == 1)
        pthread_mutex_lock(&writeLock); // First reader blocks writer
    pthread_mutex_unlock(&mutexLock);

    cout << "[Reader] Reading data: " << data << endl;
    sleep(1);

    pthread_mutex_lock(&mutexLock);
    readers--;
    if (readers == 0)
        pthread_mutex_unlock(&writeLock); // Last reader allows writer
    pthread_mutex_unlock(&mutexLock);
    return NULL;
}

void* writerSync(void*) {
    pthread_mutex_lock(&writeLock);
    data++;
    cout << "[Writer] Writing data: " << data << endl;
    sleep(1);
    pthread_mutex_unlock(&writeLock);
    return NULL;
}

void* readerNoSync(void*) {
    cout << "[Reader] Reading data (no sync): " << data << endl;
    sleep(1);
    return NULL;
}

void* writerNoSync(void*) {
    data++;
    cout << "[Writer] Writing data (no sync): " << data << endl;
    sleep(1);
    return NULL;
}

int main() {
    pthread_t r1, r2, w1, w2;
    int choice;

    pthread_mutex_init(&mutexLock, NULL);
    pthread_mutex_init(&writeLock, NULL);

    cout << "1. Without Synchronization\n2. With Synchronization\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        pthread_create(&r1, NULL, readerNoSync, NULL);
        pthread_create(&w1, NULL, writerNoSync, NULL);
        pthread_create(&r2, NULL, readerNoSync, NULL);
        pthread_create(&w2, NULL, writerNoSync, NULL);
    } else {
        pthread_create(&r1, NULL, readerSync, NULL);
        pthread_create(&w1, NULL, writerSync, NULL);
        pthread_create(&r2, NULL, readerSync, NULL);
        pthread_create(&w2, NULL, writerSync, NULL);
    }

    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w2, NULL);

    pthread_mutex_destroy(&mutexLock);
    pthread_mutex_destroy(&writeLock);

    return 0;
}
