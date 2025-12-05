#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int read_input(char* buffer, FILE* fp) {
    char c;
    int i = 0;
    while(c = fgetc(fp)) {
        if (c == ',' || c == EOF) {
            buffer[i] = '\0';
            break;
        }
        buffer[i++] = c;
    }
    return i;
}

int is_invalid_id(char* num) {
    int size = strlen(num);
    if (size > 1 && size % 2 == 0) {
        int i = 0;
        int r_i = size / 2;
        while(num[r_i] && num[i] == num[r_i] ) {
            i++;
            r_i++;
        }
        return r_i == size;
    }
    return false;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("missing input file name");
        return -1;
    }
    FILE *fp = fopen(argv[1] , "r");
    char buffer[100];
    long sum = 0;
    while(read_input(buffer, fp)) {
        char* part = strtok(buffer, "-");
        long num[2];
        int i = 0;
        while(part != NULL) {
            num[i++] = atol(part);
            part = strtok(NULL, "-");
        }
        char buf[64];
        while(num[0] <= num[1]) {
            sprintf(buf, "%ld", num[0]);
            if (is_invalid_id(buf)) {
                printf("%ld\n", num[0]);
                sum += num[0];
            }
            num[0]++;
        }
    }
    printf("Total sum of invalid IDs: %ld", sum);
    fclose(fp);
}
