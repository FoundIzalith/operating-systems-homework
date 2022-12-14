//consumer.c

//This program consumes output produced by producer.c 

//This program adds together 2 ints passed to it by the producer

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

sem_t semaphore; 
int shmid;

typedef struct buffer_s {
    char table[2];
} buffer_t;

buffer_t *buffer;

int main() {
    shmid = shmget(10312022, sizeof(buffer), 0666); //get shared memory segment created by sender
    buffer = shmat(shmid, NULL, 0); //attach to shared memory segment

    sem_open("/prodConsSem", 0x0008, 0x0002, 2);
    sem_wait(&semaphore);

    printf("Consumer has entered critical section.");

    printf("The integers received from the producer are: ");
    printf("%d", buffer->table[0]);
    printf("%d", buffer->table[1]);
    
    int sum = buffer->table[0] + buffer->table[1];
    printf("The sum of the 2 inputted integers is %d", sum);

    sem_post(&semaphore);

    return 0;
}