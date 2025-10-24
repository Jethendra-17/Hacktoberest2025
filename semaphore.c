#include <stdio.h>
 #include <semaphore.h>
 #include <pthread.h>
 int buffer[10];
 int in = 0, out = 0, item = 0, size;
 sem_t empty, full;
 pthread_mutex_t mutex;
 int main() {
    int choice;
    printf("Enter buffer size: ");
    scanf("%d", &size);
    sem_init(&empty, 0, size);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (sem_trywait(&empty) == 0) {
                    pthread_mutex_lock(&mutex);
                    item++;
                    buffer[in] = item;
                    printf("Produced item %d\n", item);
                    in = (in + 1) % size;
                    pthread_mutex_unlock(&mutex);
                    sem_post(&full);
                } else printf("Buffer full!\n");
                break;
            case 2:
                if (sem_trywait(&full) == 0) {
                    pthread_mutex_lock(&mutex);
                    int consumed = buffer[out];
                    printf("Consumed item %d\n", consumed);
                    out = (out + 1) % size;
                    pthread_mutex_unlock(&mutex);
                    sem_post(&empty);
                } else printf("Buffer empty!\n");
                break;
            case 3: return 0;
        }
    }
 
