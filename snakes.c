#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"

void Setup(void) {
  /* WINDOW *currentWindow = stdscr; */
  
  WINDOW *border = newwin(LINES - 3, COLS - 1, 2, 0);
  refresh();

  PrintGameName(stdscr, 1);
  box(border, 0, 0);
  AddFood();
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
  snakeHead->x = midX;
  snakeHead->y = midY;
  snakeHead->direction = DOWN;
  snakeHead->speed = BASESPEED;
  mvaddch(midY, midX, ACS_DARROW);
  refresh();
  return snakeHead;
}

void ChangeDirection(int direction, struct snakeNode *head) {
  int midY = (LINES - 3) / 2;
  int midX = (COLS - 1) / 2;

  head->direction = direction;
  /* mvaddch(head->y, head->x, direction); */
  /* refresh(); */
}

void MoveSnake(struct snakeNode *head) {
  int nextX;
  int nextY;
  chtype nextDirection;
  if (head->direction == UP) {
    nextX = head->x;
    nextY = head->y - 1;
    nextDirection = ACS_UARROW;
  }
  else if (head->direction == DOWN) {
    nextX = head->x;
    nextY = head->y + 1;
    nextDirection = ACS_DARROW;
  }
  else if (head->direction == LEFT) {
    nextX = head->x - 1;
    nextY = head->y;
    nextDirection = ACS_LARROW;
  }
  else if (head->direction == RIGHT) {
    nextX = head->x + 1;
    nextY = head->y;
    nextDirection = ACS_RARROW;
  }

  
  mvaddch(nextY, nextX, nextDirection);
  mvaddch(head->y, head->x, 32);
  head->y = nextY;
  head->x = nextX;
}

void *movementThread(void *arg) {
  struct snakeNode *head = (struct snakeNode*)arg;
  while(1) {
    
    usleep(head->speed);
    MoveSnake(head);
    refresh();
  }
  return 0;
}


  
