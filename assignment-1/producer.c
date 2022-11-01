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
void *sharedMemory; 

struct buffer_t {
    int table[2];
    int in;
    int out;
} buffer;

int main() {    
    int shmid;
    shmid = shmget(10312022, sizeof(buffer), 0666 | IPC_CREAT); //create shared memory
    printf("Enter an integer: ");
    read(0, buffer.table, 2);

    return 0;
}