#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int original_pos;
    int next_pos;
    int pass_zero_count;
    char dir;
} Movement;

Movement move(int current_pos, char* movement) {
    int steps = atoi(movement + 1);
    int next_steps = steps;
    if (*movement == 'L') {
        next_steps = -steps;
    }
    int end_pos = current_pos + next_steps;
    while(end_pos < 0) {
        end_pos += 100;
    }
    while(end_pos >= 100) {
        end_pos -= 100;
    }
    if (current_pos == 0 ) {
        steps -= *movement == 'L' ? 100 - end_pos : end_pos;
    }
    int target_pos = end_pos + steps;
    int pass_zero_count;
    while(target_pos >= 100) {
        target_pos -= 100;
        pass_zero_count++;
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
    char text[100];
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
        int offset = sprintf(text, "%s %d to %d", buffer, current_pos, m.next_pos);
        if (m.pass_zero_count > 0) {
            offset += sprintf(text + offset, ", dial through zero count: %d", m.pass_zero_count);
        }
        if (m.next_pos == 0) {
            offset += sprintf(text + offset, ", stays at zero");
        }
        printf("%s\n", text);
        current_pos = m.next_pos;
    }
    printf("AOC 2025 day 1, answer %d", password);
    return 0;
}
