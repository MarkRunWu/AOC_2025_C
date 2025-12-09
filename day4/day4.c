#include "../common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vec2 {
  int x;
  int y;
};

void dump(char **map, int w, int h) {
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      printf("%c", map[j][i]);
    }
    printf("\n");
  }
}

void dump_neighbors(int *map, int w, int h) {
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      printf("%d", map[j * w + i]);
    }
    printf("\n");
  }
}

void update_neighbor_rolls(int *map, char **cmap, int w, int h,
                           struct vec2 *dirs) {
  int x, y;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      if (cmap[j][i] == '@') {
        for (int k = 0; k < 8; k++) {
          x = i + dirs[k].x;
          y = j + dirs[k].y;
          if (x < 0 || x >= w || y < 0 || y >= h) {
            continue;
          }
          map[y * w + x]++;
        }
      }
    }
  }
}

int mark_movable_rolls(int *map, char **cmap, int w, int h) {
  int sum = 0;
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      if (cmap[j][i] == '@' && map[j * w + i] < 4) {
        cmap[j][i] = 'x';
        sum++;
      }
    }
  }
  return sum;
}

int remove_neighbor_rolls(int *map, char **cmap, int w, int h,
                          struct vec2 *dirs) {
  int sum = 0;
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      if (cmap[j][i] == 'x') {
        cmap[j][i] = '.';
        sum++;
        int x, y;
        for (int k = 0; k < 8; k++) {
          x = i + dirs[k].x;
          y = j + dirs[k].y;
          if (x >= 0 && x < w && y >= 0 && y < h) {
            map[y * w + x]--;
          }
        }
      }
    }
  }
  return sum;
}

int part1(int *map, char **cmap, int w, int h, struct vec2 *dirs) {
  update_neighbor_rolls(map, cmap, w, h, dirs);
  return mark_movable_rolls(map, cmap, w, h);
}

int part2(int *map, char **cmap, int w, int h, struct vec2 *dirs) {
  int s = 0;
  int total = 0;
  update_neighbor_rolls(map, cmap, w, h, dirs);
  do {
    s = mark_movable_rolls(map, cmap, w, h);
    dump(cmap, w, h);
    remove_neighbor_rolls(map, cmap, w, h, dirs);
    dump(cmap, w, h);
    total += s;
  } while (s > 0);
  return total;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("./a.out input.txt 10");
    return -1;
  }
  FILE *fp = fopen(argv[1], "r");
  int lines = 0;
  int map_size = atoi(argv[2]);
  int w = map_size;
  int h = map_size;
  char buffer[map_size];
  char **cmap = malloc(h * sizeof(char *));
  while (read_input(buffer, fp, '\n')) {
    cmap[lines] = malloc(w * sizeof(char *));
    memcpy(cmap[lines], buffer, strlen(buffer));
    lines++;
  }
  int *map = malloc(w * h * sizeof(int));

  struct vec2 dirs[8];
  dirs[0].x = 0;
  dirs[0].y = 1;
  dirs[1].x = 1;
  dirs[1].y = 1;
  dirs[2].x = 1;
  dirs[2].y = 0;
  dirs[3].x = 1;
  dirs[3].y = -1;
  dirs[4].x = 0;
  dirs[4].y = -1;
  dirs[5].x = -1;
  dirs[5].y = -1;
  dirs[6].x = -1;
  dirs[6].y = 0;
  dirs[7].x = -1;
  dirs[7].y = 1;

  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
      map[j * w + i] = 0;
    }
  }

  // int sum = part1(map, cmap, w, h, dirs);
  int sum = part2(map, cmap, w, h, dirs);

  printf("sum: %d\n", sum);
}
