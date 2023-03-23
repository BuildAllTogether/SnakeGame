#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"

void AddFood(WINDOW *border) {
  srand(time(NULL));

  /* mvprintw(0,0, "%d, %d \n", COLS, LINES); */
  // formula  num = (rand() % (upper – lower + 1)) + lower
  int x = (rand() % (COLS + 1));
  int y = (rand() % (LINES + 1));
  wmove(border, y, x);

  while(winch(border) != EMPTY) {
    x = (rand() % (COLS + 1));
    y = (rand() % (LINES + 1));
    wmove(border, y, x);
  }

  waddch(border, FOOD);
  wrefresh(border);
}
    
