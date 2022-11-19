//producer.c

//This program produces output to be read by a consumer process
//found in consumer.c

//Takes in 2 integers from the user
//Input is passed to the consumer, which adds them together and prints the value

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t semaphore; 
int shmid;

typedef struct buffer_s {
    int table[2];
} buffer_t;

buffer_t *buffer; 

int main() {    
    shmid = shmget(10312022, sizeof(buffer_t), 0666 | IPC_CREAT); //create shared memory
    buffer = (buffer_t*) shmat(shmid, NULL, 0); //attach to shared memory segment 
    
    sem_open("/prodConsSem", 0x0008, 0x0002, 1);
    sem_wait(&semaphore);

    printf("Producer has entered critical section.");

    for(int i = 0; i < 2; i++) {
        printf("Enter integer #%d: ", i);
        scanf("%d", &buffer->table[i]);
    }

    printf("Input received! Sending to consumer...\n");

    sem_post(&semaphore);
    

    return 0;
}