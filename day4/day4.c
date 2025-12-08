#include "../common.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("./a.out input.txt");
    return -1;
  }
  char buffer[100];
  FILE *fp = fopen(argv[1], "r");
  while (read_input(buffer, fp, '\n')) {
    printf("%s\n", buffer);
  }
}
