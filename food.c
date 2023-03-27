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
  
  int x = (rand() % (maxX - startX + 1)) + startX;
  int y = (rand() % (maxY - startY + 1)) + startY;

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
    
