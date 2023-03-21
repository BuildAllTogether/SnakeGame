#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "snakes.h"
#include "food.h"


struct snakeNode *InitSnake(WINDOW *border) {
  int midY = (LINES - 3) / 2;
  int midX = (COLS - 1) / 2;

  struct snakeNode *snakeHead = malloc(sizeof(struct snakeNode));
  snakeHead->x = midX;
  snakeHead->y = midY;
  snakeHead->direction = DOWN;
  snakeHead->speed = BASESPEED;
  snakeHead->border = border;
  mvwaddch(border, midY, midX, ACS_DARROW);
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

  char curch = mvwinch(head->border, nextY, nextX);

  mvwaddch(head->border, nextY, nextX, nextDirection);
  mvwaddch(head->border, head->y, head->x, 32);
  head->y = nextY;
  head->x = nextX;


  if (curch == FOOD) {
    AddFood(head->border);
  }

}

void *movementThread(void *arg) {
  struct snakeNode *head = (struct snakeNode*)arg;
  while(1) {
        /* refresh(); */
    usleep(head->speed);
    MoveSnake(head);
    wrefresh(head->border);
  }
  return 0;
}


  
