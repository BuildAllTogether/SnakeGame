#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"


int main(int argc, char *argv[]) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  Setup();
  struct snakeNode *head = InitSnake();
  while(1) {
    int key = getch();

    switch(key) {
    case KEY_UP:
      ChangeDirection(ACS_UARROW, head);
      break;
    case KEY_DOWN:
      ChangeDirection(ACS_DARROW, head);
      break;
    case KEY_LEFT:
      ChangeDirection(ACS_LARROW, head);
      break;
    case KEY_RIGHT:
      ChangeDirection(ACS_RARROW, head);
      break;
    case 'q':
      break;
    }

  }
  

  return 0;
}

