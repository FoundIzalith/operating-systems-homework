//producer.c

//This program produces output to be read by a consumer process
//found in consumer.c

//Takes in integers from the user until it reads in 0.
//Input is passed to the consumer, which doubles and prints it

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t semaphore; 

struct buffer_t {
    char table[2];
    int in;
    int out;
} buffer;

int main() {
    semaphore = sem_open("/producerConsumerPipe", 0_CREAT, permissions, 0);
    
    shmget(producerConsumerMem, 4, NULL); //create shared memory

    return 0;
}