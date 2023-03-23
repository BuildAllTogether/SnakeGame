#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"

void AddFood(WINDOW *border) {
  srand(time(NULL));

  /* mvprintw(0,0, "%d, %d \n", COLS, LINES); */
  int x = (rand() % (COLS - 1 - 2 + 1)) + 2;
  int y = (rand() % (LINES - 3 + 4 + 1)) + 4;
  wmove(border, y, x);

  while(winch(border) != EMPTY) {
    x = (rand() % (COLS - 1 - 2 + 1)) + 2;
    y = (rand() % (LINES - 3 + 4 + 1)) + 4;
    wmove(border, y, x);
  }

  waddch(border, FOOD);
  wrefresh(border);
}
    
