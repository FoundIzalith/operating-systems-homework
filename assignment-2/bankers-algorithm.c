#include <stdio.h>

struct systemResources_t {
    int ResourceAMax;
    int ResourceBMax;
    int ResourceCMax;

    int ResourceAAlloc;
    int ResourceBAlloc;
    int ResourceCAlloc;

} systemResources;

struct process_T {
    int requestA;
    int requestB;
    int requestC;
};

//Pass data file as input
int main(int argc, char *argv[]) {
    
    while(argc--) {
        printf("%s\n", argv[argc]);
    }

    return 0;
}

int requestResource() {

}