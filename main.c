#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"


int main(int argc, char *argv[]) {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  Setup();
  while(1) {
    /* int key = getch(); */

  }

  return 0;
}

