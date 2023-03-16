#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"


void Setup(void) {
  /* WINDOW *currentWindow = stdscr; */
  
  WINDOW *border = newwin(LINES - 3, COLS - 1, 2, 0);
  refresh();

  PrintGameName(stdscr, 1);
  box(border, 0, 0);

  refresh();
  wrefresh(border);


}

void PrintGameName(WINDOW *win, int startRow) {
  int centerCol = win->_maxx / 2;
  int halfLength = 10 / 2;

  int adjustedCol = centerCol - halfLength;

  mvwprintw(win, startRow, adjustedCol, "Snake Game!");
}


struct snakeNode *InitSnake(void) {
  int midY = (LINES - 3) / 2;
  int midX = (COLS - 1) / 2;

  struct snakeNode *snakeHead = malloc(sizeof(struct snakeNode));
  
  mvaddch(midY, midX, ACS_DARROW);
  refresh();
  return snakeHead;
}

void ChangeDirection(chtype direction, struct snakeNode *head) {
  int midY = (LINES - 3) / 2;
  int midX = (COLS - 1) / 2;

  head->direction = direction;
  mvaddch(midY, midX, direction);
  refresh();
}


  
