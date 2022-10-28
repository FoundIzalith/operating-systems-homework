//consumer.c

//This program consumes output produced by producer.c 

//This program doubles ints passed to it by the producer

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t semaphore; 

int main() {
    semaphore = sem_open("/producerConsumerPipe", 0_CREAT, permissions, 0);



    return 0;
}