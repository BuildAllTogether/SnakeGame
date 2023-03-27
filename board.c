#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <stdbool.h>


#include "snakes.h"
#include "board.h"
#include "food.h"


struct allwindows *Setup(void) {
  /* WINDOW *currentWindow = stdscr; */
  
  /* WINDOW *border = newwin(LINES - 3, COLS - 1, 2, 0); */
  WINDOW *border = newwin(LINES / 2, COLS /3 , LINES / 4, COLS / 3);
  WINDOW *gameName = newwin(3, 20, 10, COLS / 3 + 24);
  WINDOW *score = newwin(LINES / 2 + 2, 20, LINES - 14, COLS / 3 + 1);
  struct allwindows *allWindows = (struct allwindows *) malloc(sizeof(struct allwindows));
  allWindows->board = border;
  allWindows->name = gameName;
  allWindows->score = score;
  
  refresh();
  PrintGameName(gameName);
  PrintScore(score);
  box(border, 0, 0);
  refresh();
  AddFood(border);
  wrefresh(border);
  return allWindows;
}

void PrintGameName(WINDOW *win) {
  mvwprintw(win, 1, 5, "Snake Game!");
  wrefresh(win);
}

void PrintScore(WINDOW *win) {
  wprintw(win, "Score: 0");
  wrefresh(win);
}


