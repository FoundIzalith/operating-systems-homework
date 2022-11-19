#include <stdio.h>

#define n_Resources 3
#define n_Processes 5

int systemMax[n_Resources] = {10, 5, 7}; //Total # of resources in system    
//Banker's data 
int available[n_Resources]; //Unallocated resources
int max[n_Processes][n_Resources]; //Max of a given resource a process may request
int allocation[n_Processes][n_Resources]; //Current # of resources allocated to process
int need[n_Processes][n_Resources]; //# of resources a process needs

int readInFile(char **argv);

//Pass data file as input
int main(int argc, char **argv) {
    if (argv[1] == NULL) {
        printf("bankers-algorithm requires a minimum of 1 parameter.");
        printf("Please run as: ./bankers-algorithm [filename]");
    }

    //File input functions moved to another function for the sake of readability 
    //Side effect: sets values of all the banker's data
    int read = readInFile(argv);
    if (read == 1) return 1; 

    return 0;
}

int readInFile(char **argv) {
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Failed to open \"%s\", exiting.\n", argv[1]);
        return 1;
    }

    printf("Successfully opened \"%s\"\n", argv[1]);

    char buffer[100];

    //I hate to code a file input like this but I think a better solution
    //would be overly complicated for this sort of project. I know this is awful.
    //Just make sure any custom input is in the same format as the provided file.
    for(int i = 0; i < 5; ++i) {
        fscanf(file, "%s", buffer);
        allocation[i][0] = buffer[0];
        allocation[i][1] = buffer[2];
        allocation[i][2] = buffer[4];
        max[i][0] = buffer[6];
        max[i][1] = buffer[8];
        max[i][2] = buffer[10];
        
        if(i == 0) {
            available[0] = buffer[12];
            available[1] = buffer[14];
            available[2] = buffer[16];
        }
    }

    fclose(file);

    return 0;
}
