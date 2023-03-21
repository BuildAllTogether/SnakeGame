#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"
#include "board.h"

WINDOW * Setup(void) {
  /* WINDOW *currentWindow = stdscr; */
  
  WINDOW *border = newwin(LINES - 3, COLS - 1, 2, 0);

  PrintGameName(stdscr, 1);
  box(border, 0, 0);
  refresh();
  AddFood(border);
  wrefresh(border);
  return border;
}

void PrintGameName(WINDOW *win, int startRow) {
  int centerCol = win->_maxx / 2;
  int halfLength = 10 / 2;

  int adjustedCol = centerCol - halfLength;

  mvwprintw(win, startRow, adjustedCol, "Snake Game!");
}

