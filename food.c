#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"

void AddFood(void) {
  int x;
  int y;
  while(inch() != EMPTY) {
    // random in range is num = (rand() % (upper - lower + 1) + lower
    x = (rand() % (COLS));
    y = (rand() % (LINES + 1)) + 3;
    move(y, x);
  }
  addch(FOOD);
}
    
