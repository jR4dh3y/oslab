#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define BUFFER_MAX 32
int BUFFER[BUFFER_MAX], BUFFER_SIZE = 0;


int empty = 1, full = 1, mutex = 1;

void wait_sem(int *s){
    while( *s <= 0);
    *s -= 1;
}

void signal_sem(int *s){
    *s += 1;
}

void *producer(int *id){
    int item;
    do {
        wait_sem(&empty);
        wait_sem(&mutex);

        printf("Producer %d obtained mutex\n", id);
        
        while(BUFFER_SIZE < BUFFER_MAX){
            item = rand() % 100;
            BUFFER[BUFFER_SIZE++] = item;
        }

        signal_sem(&mutex);
        signal_sem(&full);

    }while(1);
    
}

void *consumer(int *id){
    int item = 0;
    do{
        wait_sem(&full);
        wait_sem(&mutex);

        item = BUFFER[BUFFER_SIZE--];
        if (BUFFER_SIZE < 0) BUFFER_SIZE = 0;
        printf("Consumer %d consumed %d\n", id, item);

        
        signal_sem(&mutex);
        signal_sem(&empty);

    }while(1);
}


int main(int argc, char **argv){
    if (argc != 3){
        printf("Usage: %s <producers> <consumers>\n", argv[0]);
        return 1;
    }

    int producers = atoi(argv[1]);
    int consumers = atoi(argv[2]);

    pthread_t producer_threads[producers];
    pthread_t consumer_threads[consumers];

    for (int i = 0; i < producers; i++){
        printf("Creating producer with id: %d\n", i);
        pthread_create(&producer_threads[i], NULL, (void *)producer, (void *) i+1);
    }

    for (int i = 0; i < consumers; i++){
        printf("Creating consumer with id: %d\n", i);
        pthread_create(&consumer_threads[i], NULL, (void *)consumer, (void *) i +1 );
    }
    for (int i = 0; i < producers; i++){
        pthread_join(producer_threads[i], NULL);
    }

    return 0;
}
