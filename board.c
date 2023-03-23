#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"
#include "board.h"

WINDOW * Setup(void) {
  /* WINDOW *currentWindow = stdscr; */
  
  /* WINDOW *border = newwin(LINES - 3, COLS - 1, 2, 0); */
  WINDOW *border = newwin(LINES / 2, COLS /3 , LINES / 4, COLS / 3);
  WINDOW *gameName = newwin(3, 20, 10, COLS / 3 + 24);
  refresh();
  PrintGameName(gameName);
  box(border, 0, 0);
  refresh();
  AddFood(border);
  wrefresh(border);
  return border;
}

void PrintGameName(WINDOW *win) {
  mvwprintw(win, 1, 5, "Snake Game!");
  wrefresh(win);
}

void Quit(int reason, WINDOW *border) {
  
}
