#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"

void AddFood(WINDOW *border) {
  srand(time(NULL));

  /* mvprintw(0,0, "%d, %d \n", COLS, LINES); */
  // formula  num = (rand() % (upper – lower + 1)) + lower
  int x = (rand() % (COLS / 3 - COLS / 8 + 1)) + COLS / 8;
  int y = (rand() % (LINES / 2 - LINES / 6 + 1)) + LINES / 6;
  wmove(border, y, x);

  while(winch(border) != EMPTY) {
    x = (rand() % (COLS / 3 - COLS / 4 + 1)) + COLS / 4;
    y = (rand() % (LINES / 3 - LINES / 4+ 1)) + LINES / 4;
    wmove(border, y, x);
  }

  waddch(border, FOOD);
  wrefresh(border);
}
    
