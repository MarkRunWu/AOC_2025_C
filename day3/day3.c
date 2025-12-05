#include<stdio.h>
#include<stdlib.h>
#include "../common.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("missing input file name");
        return -1;
    }
    FILE *fp = fopen(argv[1] , "r");
    char buffer[100];
    while(read_input(buffer, fp, '\n')) {
        printf("%s\n", buffer);
    }
}
