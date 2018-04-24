#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

#include <ncurses.h>

#define HEIGHT 45
#define WIDTH 10

uint16_t top_color = 0;
uint16_t middle_color = 0;
uint16_t bottom_color = 0;
uint16_t black = 0;

uint8_t add_count = 0;

int main (int argc, char * argv[]) {
  srand(clock());
  uint16_t * boardmap = calloc(HEIGHT * WIDTH, sizeof(*boardmap));
  int ch = 0;
  initscr();
  raw();
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
  timeout(100);
  while (ch != 'q') {
    erase();
    for (int y = HEIGHT - 1; y > 0; --y) {
      for (int x = 0; x < WIDTH; x++) {
        boardmap[y * WIDTH + x] = boardmap[(y-1) * WIDTH + x];
      }
    }
    // Clear the top row
    for (int x = 0; x < WIDTH; x++) {
      boardmap[x] = 0;
    }

    // Randomly create some new rain
    add_count = rand() % WIDTH;
    for (int i = 0; i < add_count; i++) {
      boardmap[rand() % WIDTH] = 1;
    }
    for (int x = 0; x < WIDTH; x++) {
      for (int y = 0; y < HEIGHT; y++) {
        if (boardmap[y * WIDTH + x] == 0) {
          printw(" ");
        } else {
          printw("1");
        }
    }
      printw("\n");
    }
    refresh();
    ch = getch();
  }
  endwin();
  free(boardmap);
  exit(EXIT_SUCCESS);
}
