#include <stdio.h>
#include <stdbool.h>

#define n_Resources 3
#define n_Processes 5

int systemMax[n_Resources] = {10, 5, 7}; //Total # of resources in system    
//Banker's data 
int available[n_Resources]; //Unallocated resources
int max[n_Processes][n_Resources]; //Max of a given resource a process may request
int allocation[n_Processes][n_Resources]; //Current # of resources allocated to process
int need[n_Processes][n_Resources]; //# of resources a process needs

int safeSequence[n_Processes];

int readInFile(char **argv); 
bool safety();
void resourceRequest();
 
//Pass data file as input
int main(int argc, char **argv) {
    if (argv[1] == NULL) {
        printf("bankers-algorithm requires a minimum of 1 parameter.\n");
        printf("Please run as: ./bankers-algorithm [filename]\n");
        return 1;
    }

    //File input functions moved to another function for the sake of readability 
    //Side effect: sets values of all the banker's data
    int read = readInFile(argv);
    if (read == 1) return 1; 

    //Set need and finished initial values 
    for(int i = 0; i < n_Processes; i++) {
        for(int j = 0; j < n_Resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    //Run safety algorithm
    bool safe = safety();

    if (safe == true)  {
        printf("The system is in a safe state.\n");
        printf("The safe sequence is: ");
        for(int i = 0; i < n_Processes; i++) {
            printf(" P%d ->", safeSequence[i]);
        }
    }

    if (safe == false) printf("The system is in an unsafe state.\n");
    
    return 0;
}

//Returns 0 if read is successful, else returns 1
//Side effect: sets values of all the banker's data
int readInFile(char **argv) {
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Failed to open \"%s\", exiting.\n", argv[1]);
        return 1;
    }

    printf("Successfully opened \"%s\"\n", argv[1]);

    char buffer[32];

    //I hate to code a file input like this but I think a better solution
    //would be overly complicated for this sort of project. I know this is awful.
    //Just make sure any custom input is in the same format as the provided file.
    for(int i = 0; i < 5; ++i) {
        //fscanf(file, "%s", buffer);
        fgets(buffer, 32, file);
        allocation[i][0] = (int)buffer[0] - (int)'0';
        allocation[i][1] = (int)buffer[2] - (int)'0';
        allocation[i][2] = (int)buffer[4] - (int)'0';
        max[i][0] = (int)buffer[6] - (int)'0';
        max[i][1] = (int)buffer[8] - (int)'0';
        max[i][2] = (int)buffer[10] - (int)'0';
        
        if(i == 0) {
            available[0] = (int)buffer[12] - (int)'0';
            available[1] = (int)buffer[14] - (int)'0';
            available[2] = (int)buffer[16] - (int)'0';
        }
    }

    fclose(file);

    printf("Allocation matrix:\n");
    for(int i = 0; i < n_Processes; i++) {
        for(int j = 0; j < n_Resources; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("Max matrix:\n");
    for(int i = 0; i < n_Processes; i++) {
        for(int j = 0; j < n_Resources; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("Available resources:\n");
    for(int i = 0; i < n_Resources; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    return 0;
}

//Safety algorithm
//Returns true if system is in safe state, else returns false 
bool safety() {
    bool finished[n_Processes];
    bool flag = false; 
    int index = 0; 

    //Set initial values of finished and work arrays
    for(int i = 0; i < n_Processes; i++) {
        finished[i] = false;
    }
 
    for(int i = 0; i < n_Processes; i++) {
        for(int j = 0; j < n_Processes; j++) {
            /*if(finished[i] == false && need[i][j] <= work[j]) { 
                work[j] = work[j] + allocation[i][j];
                finished[i] = true;
            }*/
            if(finished[i] == false) {
                flag = false; 
                for(int k = 0; k < n_Resources; k++) {
                    if(need[j][k] > available[k]) {
                        flag = true;
                        break;
                    }
                }

                if(flag == false) {
                    safeSequence[index++] = i;
                    for(int k = 0; k < n_Resources; k++) {
                        available[k] += allocation[j][k];
                    }

                    finished[j] = true; 
                }
            }
        }
    }

    //If all processes are finished then the system is in a safe state 
    for(int i = 0; i < n_Processes; i++) {
        if (finished[i] == false) {
            printf("Process %d is unfinished\n", i);
            return false;
        }
    }

    return true;
}

