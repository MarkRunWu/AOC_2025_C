#include "../common.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

struct Range {
  long min;
  long max;
};

int part1(struct Range **ranges, int range_size, long *nums, int nums_size) {
  int sum = 0;
  for (int j = 0; j < nums_size; j++) {
    int is_fresh = 0;
    long num = nums[j];
    for (int i = 0; i < range_size; i++) {
      if (num >= ranges[i]->min && num <= ranges[i]->max) {
        is_fresh = 1;
        break;
      }
    }
    if (is_fresh) {
      sum++;
    }
  }
  return sum;
}

int part2(struct Range **ranges, int range_size) { return 0; }

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("./a.out input.txt");
    return -1;
  }

  char buffer[100];
  FILE *fp = fopen(argv[1], "r");

  // read valid ranges
  int range_size = 0;
  int range_buffer_size = 10;
  struct Range **ranges = malloc(10 * sizeof(struct Range *));
  while (read_input(buffer, fp, '\n')) {
    if (range_size >= range_buffer_size) {
      range_buffer_size *= 2;
      ranges = realloc(ranges, range_buffer_size * sizeof(struct Range *));
    }
    struct Range *r = malloc(sizeof(struct Range));
    char *tmp;
    r->min = atol(strtok_r(buffer, "-", &tmp));
    r->max = atol(strtok_r(NULL, "-", &tmp));
    ranges[range_size] = r;
    range_size++;
  }

  // read ids
  int nums_size = 0;
  int num_buffer_size = 10;
  long *nums = malloc(num_buffer_size * sizeof(long));
  while (read_input(buffer, fp, '\n')) {
    if (nums_size >= num_buffer_size) {
      num_buffer_size *= 2;
      nums = realloc(nums, num_buffer_size * sizeof(long));
    }
    nums[nums_size++] = atol(buffer);
  }
  printf("Part 1: %d\nPart 2: %d", part1(ranges, range_size, nums, nums_size),
         part2(ranges, range_size));
  return 0;
}
