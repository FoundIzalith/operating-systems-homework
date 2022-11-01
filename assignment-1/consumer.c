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
void *sharedMemory;

struct buffer_t {
    char table[2];
    int in;
    int out;
} buffer;

int main() {
    shmid = shmget(10312022, sizeof(buffer), 0666);
    printf


    return 0;
}