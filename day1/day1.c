#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int original_pos;
    int next_pos;
    int pass_zero_count;
    char dir;
} Movement;

Movement move(int current_pos, char* movement) {
    int next_steps = atoi(movement + 1);
    if (*movement == 'L') {
        next_steps = -next_steps;
    }
    int end_pos = current_pos + next_steps;
    int pass_zero_count = 0;
    while(end_pos < 0) {
        pass_zero_count += 1;
        end_pos += 100;
    }
    while(end_pos >= 100) {
        pass_zero_count += 1;
        end_pos -= 100;
    }

    Movement m = { 
        current_pos,
        end_pos,
        pass_zero_count,
        *movement
    };
    return m;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("missing input file name");
        return -1;
    }
    FILE *fp = fopen(argv[1] , "r");

    char buffer[100];
    int current_pos = 50;
    int password = 0;
    Movement pre = {};
    while(fgets(buffer, sizeof(buffer), fp)) {
        Movement m = move(current_pos, buffer);
        if (m.next_pos == 0) {
            password++;
        }
        password += m.pass_zero_count;

        pre = m;
        printf("%s %d to %d, dial through zero count: %d\n",buffer, current_pos, m.next_pos, m.pass_zero_count);
        current_pos = m.next_pos;
        printf("password: %d\n", password);
    }
    printf("AOC 2025 day 1, answer %d", password);
    return 0;
}
