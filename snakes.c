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
  int nextX = head->x;
  int nextY = head->y;
  chtype nextDirection;
  if (head->direction == UP) {
    nextY -= 1;
    nextDirection = ACS_UARROW;
  }
  else if (head->direction == DOWN) {
    nextY += 1;
    nextDirection = ACS_DARROW;
  }
  else if (head->direction == LEFT) {
    nextX -= 1;
    nextDirection = ACS_LARROW;
  }
  else if (head->direction == RIGHT) {
    nextX += 1;
    nextDirection = ACS_RARROW;
  }

  char curch = mvwinch(head->border, nextY, nextX);

  mvwaddch(head->border, nextY, nextX, nextDirection);
  /* mvwaddch(head->border, head->y, head->x, 32); */
  /* head->y = nextY; */
  /* head->x = nextX; */
  

  if (curch == FOOD) {
    AddFood(head->border);
    IncreaseBody(head);
  }
  else {
    struct snakeNode *tail = GetTail(head);
    mvwaddch(head->border, tail->y, tail->x, 32);
    ShiftLocation(head, nextX, nextY);
  }

  head->y = nextY;
  head->x = nextX;
    

}

struct snakeNode* GetTail(struct snakeNode *head) {
  struct snakeNode *cur = head;
  
  while (cur->next != NULL) {
    cur = cur->next;
  }
  
  return cur;
}
 
void ShiftLocation(struct snakeNode *head, int nextX, int nextY) {

  if (head->next != NULL) {
    struct snakeNode *cur = head;
    int bx;
    int by;
    while (cur != NULL) {
      bx = cur->x;
      by= cur->y;
      
      cur->x = nextX;
      cur->y = nextY;

      nextX = bx;
      nextY = by;
    }
  }
}


void IncreaseBody(struct snakeNode *head) {
  struct snakeNode *tail = GetTail(head);
  
  struct snakeNode *next = malloc(sizeof(struct snakeNode));
  tail->next = next;
  next->y = tail->y;
  next->x = tail->x;
  next->next = NULL;
  next->border = tail->border;
  
}


void *movementThread(void *arg) {
  struct snakeNode *head = (struct snakeNode*)arg;
  while(1) {
    usleep(head->speed);
    MoveSnake(head);
    wrefresh(head->border);
  }
  return 0;
}


  
