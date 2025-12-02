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
    int pass_zero_count = 0;
    while(end_pos < 0) {
        end_pos += 100;
        pass_zero_count++;
    }
    while(end_pos >= 100) {
        end_pos -= 100;
        pass_zero_count++;
    }
    if ((current_pos == 0 || end_pos == 0) && pass_zero_count > 0) {
        pass_zero_count--;
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
    printf("The dial starts by pointing at %d\n", current_pos);
    while(fgets(buffer, sizeof(buffer), fp)) {
        char* b = buffer;
        while(*b != '\n') {
            b++;
        }
        *b = 0;

        Movement m = move(current_pos, buffer);
        password += m.pass_zero_count;

        int offset = sprintf(text, "The dial is rotated %s to point at %d", buffer, m.next_pos);
        if (m.pass_zero_count > 0) {
            offset += sprintf(text + offset, ", during this rotation, it points at 0 (%d) times", m.pass_zero_count);
        }
        if (m.next_pos == 0) {
            password++;
        }
        printf("%s\n", text);
        current_pos = m.next_pos;
    }
    printf("AOC 2025 day 1, answer %d", password);
    return 0;
}
