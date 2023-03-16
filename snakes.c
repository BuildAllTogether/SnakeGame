#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"


void Setup(void) {
  /* WINDOW *currentWindow = stdscr; */
  
  WINDOW *border = newwin(LINES - 3, COLS - 1, 2, 0);
  /* int y, x; */
  /* getmaxyx(border, y, x); */
  /* printf("%d, %d\n", x, y); */
  refresh();

  PrintGameName(stdscr, 1);
  box(border, 124, 0);

  refresh();
  wrefresh(border);

  InitSnake();
}

void PrintGameName(WINDOW *win, int startRow) {
  int centerCol = win->_maxx / 2;
  int halfLength = 10 / 2;

  int adjustedCol = centerCol - halfLength;

  mvwprintw(win, startRow, adjustedCol, "Snake Game!");
}


void InitSnake(void) {
  int midY = (LINES - 3) / 2;
  int midX = (COLS - 1) / 2;

  mvaddch(midY, midX, ACS_DARROW);
  refresh();
}

void ChangeDirection(chtype direction) {
  int midY = (LINES - 3) / 2;
  int midX = (COLS - 1) / 2;
  
  mvaddch(midY, midX, direction);
  refresh();
}


  
