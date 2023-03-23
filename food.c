#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"

void AddFood(WINDOW *border) {
  srand(time(NULL));
  int startX;
  int startY;
  int maxX;
  int maxY;

  getparyx(border, startY, startX);
  getmaxyx(border, maxY, maxX);
  
  /* mvprintw(0,0, "%d, %d \n", COLS, LINES); */
  // formula  num = (rand() % (upper – lower + 1)) + lower
  int x = (rand() % (maxX - startX + 1)) + startX;
  int y = (rand() % (maxY - startY + 1)) + startY;
  mvprintw(0, 0, "%d, %d", startX, startY);
  mvprintw(1, 0, "%d, %d", maxX, maxY);
  wmove(border, y, x);
  wrefresh(border);

  while(winch(border) != EMPTY) {
    x = (rand() % (maxX - startX + 1)) + startX;
    y = (rand() % (maxY - startY + 1)) + startY;
    wmove(border, y, x);
    wrefresh(border);
  }

  waddch(border, FOOD);
  wrefresh(border);
}
    
