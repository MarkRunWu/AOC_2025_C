#include<stdio.h>
int read_input(char* buffer, FILE* fp, char delimiter) {
    char c;
    int i = 0;
    while(c = fgetc(fp)) {
        if (c == delimiter || c == EOF) {
            buffer[i] = '\0';
            break;
        }
        buffer[i++] = c;
    }
    return i;
}
