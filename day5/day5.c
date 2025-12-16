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

struct node {
  struct Range *d;
  struct node *next;
};

struct queue {
  struct node *head;
  struct node *tail;
};

void enqueue(struct queue *q, struct Range *data) {
  struct node *n = malloc(sizeof(struct node));
  n->d = data;
  n->next = NULL;
  if (!q->head) {
    q->head = n;
    q->tail = n;
    return;
  }
  q->tail->next = n;
  q->tail = n;
}

struct Range *dequeue(struct queue *q) {
  if (!q->head) {
    return NULL;
  }
  struct node *current = q->head;
  q->head = q->head->next;

  if (!q->head) {
    q->tail = NULL;
  }

  current->next = NULL;
  return current->d;
}

long part2(struct queue *q) {
  long sum = 0;
  struct Range *current;
  struct Range *next;
  while ((current = dequeue(q))) {
    sum += current->max - current->min + 1;
    struct queue tmp_q = {NULL, NULL};
    while ((next = dequeue(q))) {
      if (next->min > current->max || next->max < current->min) {
        // no intersection
        enqueue(&tmp_q, next);
        continue;
      }
      // split ranges
      if (current->min > next->min) {
        struct Range *l = malloc(sizeof(struct Range));
        l->min = next->min;
        l->max = current->min - 1;
        enqueue(&tmp_q, l);
      }
      if (current->max < next->max) {
        struct Range *r = malloc(sizeof(struct Range));
        r->min = current->max + 1;
        r->max = next->max;
        enqueue(&tmp_q, r);
      }
    }
    while ((next = dequeue(&tmp_q))) {
      enqueue(q, next);
    }
  }
  return sum;
}

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
  struct queue q;
  q.head = NULL;
  q.tail = NULL;
  for (int i = 0; i < range_size; i++) {
    enqueue(&q, ranges[i]);
  }
  printf("Part 1: %d\nPart 2: %ld", part1(ranges, range_size, nums, nums_size),
         part2(&q));
  return 0;
}
