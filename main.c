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
  while(1) {
    int key = getch();

    switch(key) {
    case KEY_UP:
      ChangeDirection(ACS_UARROW);
      break;
    case KEY_DOWN:
      ChangeDirection(ACS_DARROW);
      break;
    case KEY_LEFT:
      ChangeDirection(ACS_LARROW);
      break;
    case KEY_RIGHT:
      ChangeDirection(ACS_RARROW);
      break;
    case 'q':
      break;
    }
  }

  return 0;
}

