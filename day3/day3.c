#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../common.h"

int index_of_max(char* str) {
    char max = *str;
    int i = 0;
    int max_i = 0;
    while(*str != '\0') {
        if (max < *str) {
            max = *str;
            max_i = i;
        }
        i++;
        str++;
    }
    return max_i;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("./a.out input.txt 2");
        return -1;
    }
    FILE *fp = fopen(argv[1] , "r");
    char buffer[200];
    long sum = 0;
    int digit_num = atoi(argv[2]);
    while(read_input(buffer, fp, '\n')) {
        char tmp[200];
        char num[digit_num+1];
        int end = strlen(buffer) - 1;
        int l = 0;
        int r = end - (digit_num - 1);
        int i = 0;
        while(r <= end) {
            int copy_size = r - l + 1;
            memcpy(tmp, buffer + l, copy_size);
            tmp[copy_size] = '\0';
            int max_i = index_of_max(tmp);
            num[i++] = tmp[max_i];
            r++;
            l += max_i + 1;
        }
        num[i] = '\0';
        sum += atol(num);
        printf("num: %s\n", num);
    }
    printf("sum: %ld\n", sum);
}
