#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <stdbool.h>


#include "snakes.h"
#include "food.h"
#include "board.h"


struct snakeNode *InitSnake(struct allwindows *allWindows) {
  int midY = LINES / 4;
  int midX = COLS / 4;
  WINDOW *border = allWindows->board;

  struct snakeNode *snakeHead = malloc(sizeof(struct snakeNode));
  snakeHead->x = midX;
  snakeHead->y = midY;
  snakeHead->direction = malloc(sizeof(struct direction));
  snakeHead->direction->dir = DOWN;
  snakeHead->speed = BASESPEED;
  snakeHead->border = border;
  mvwaddch(border, midY, midX, ACS_DARROW);
  snakeHead->score = 0;
  snakeHead->alive = true;
  snakeHead->scoreWindow = allWindows->score;
  MoveSnake(snakeHead);
  wrefresh(border);
  return snakeHead;
}

void ChangeDirection(int direction, struct snakeNode *head) {
  
  if (NotLongerThan(head->direction, 1)) {
    struct direction *dir = GetDirectionTail(head->direction);
    struct direction *nextDir = malloc(sizeof(struct direction));
    nextDir->dir = direction;
    if (dir != NULL) {
      if (!IsOpposite(head, direction)) {
	dir->next = nextDir;
      }
    }
    else {
      head->direction = nextDir;
    }
  }
}

int DirectionLength(struct direction *direction) {
  struct direction *cur = direction;
  int directionLength = 0;
  while (cur != NULL) {
    cur = cur->next;
    directionLength += 1;
  }
  return directionLength;
}
  
void RemoveDirection(struct snakeNode *head) {
  int directionLength = DirectionLength(head->direction);
  if (directionLength >= 2) {
    head->direction = head->direction->next;
  }
}

void MoveSnake(struct snakeNode *head) {
  int nextX = head->x;
  int nextY = head->y;
  chtype nextDirection;

  if (head->direction->dir == UP) {
    nextY -= 1;
    nextDirection = ACS_UARROW;
  }
  else if (head->direction->dir == DOWN) {
    nextY += 1;
    nextDirection = ACS_DARROW;
  }
  else if (head->direction->dir == LEFT) {
    nextX -= 1;
    nextDirection = ACS_LARROW;
  }
  else if (head->direction->dir == RIGHT) {
    nextX += 1;
    nextDirection = ACS_RARROW;
  }

  char curch = mvwinch(head->border, nextY, nextX);

  mvwaddch(head->border, nextY, nextX, nextDirection);

  int maxX;
  int maxY;
  getmaxyx(head->border, maxY, maxX);
  
  if (nextX <= 0 || nextX >= maxX || nextY <= 0 || nextY >= maxY) {
    head->alive = false;
    Quit(0, head->border, head);
  }
  else if (curch == SNAKEBODY) {
    head->alive = false;
    Quit(1, head->border, head);
  }
  else if (curch == FOOD) {
    IncreaseBody(head);
    mvwaddch(head->border, head->y, head->x, SNAKEBODY);
    ShiftLocationNotTail(head,nextX, nextY);
    wprintw(head->scoreWindow, "\rScore: %d", head->score);
    wrefresh(head->scoreWindow);
    AddFood(head->border);
  }
  else {
    struct snakeNode *tail = GetSnakeTail(head);
    
    mvwaddch(head->border, head->y, head->x, SNAKEBODY);
    mvwaddch(head->border, tail->y, tail->x, 32);
    ShiftLocation(head, nextX, nextY);
  }
  RemoveDirection(head);

}

struct snakeNode* GetSnakeTail(struct snakeNode *head) {
  struct snakeNode *cur = head;
  
  while (cur->next != NULL) {
    cur = cur->next;
  }
  
  return cur;
}
 
 
struct direction *GetDirectionTail(struct direction *direction) {
  struct direction *curDir = direction;
  while (curDir->next != NULL) {
    curDir = curDir->next;
  }
  return curDir;
}
 
void ShiftLocation(struct snakeNode *head, int nextX, int nextY) {
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

      cur = cur->next;
  }
}

void ShiftLocationNotTail(struct snakeNode *head, int nextX, int nextY) {
  struct snakeNode *cur = head;
  int bx;
  int by;
  
  while (cur->next != NULL) {
      bx = cur->x;
      by= cur->y;
      
      cur->x = nextX;
      cur->y = nextY;

      nextX = bx;
      nextY = by;

      cur = cur->next;
  }
}


void IncreaseBody(struct snakeNode *head) {
  head->score += 1;
  struct snakeNode *tail = GetSnakeTail(head);
  
  struct snakeNode *next = malloc(sizeof(struct snakeNode));
  tail->next = next;
  next->y = tail->y;
  next->x = tail->x;
  next->next = NULL;
  next->border = tail->border;
  
}


void *movementThread(void *arg) {
  struct snakeNode *head = (struct snakeNode*)arg;
  while(head->alive) {
    usleep(head->speed);
    MoveSnake(head);
    wrefresh(head->border);
  }
  return 0;
}


bool NotLongerThan(struct direction *head, int length) {
  struct direction *cur = head;
  int directionLength = 0;
  while (cur != NULL) {
    cur = cur->next;
    directionLength += 1;
  }

  if (directionLength <= length) {
    return true;
  }
  else {
    return false;
  }
}


bool IsOpposite(struct snakeNode *head, int direction) {
  if (head->direction->dir == UP && direction == DOWN) {
    return true;
  }
  else if (head->direction->dir == DOWN && direction == UP) {
    return true;
  }
  else if (head->direction->dir == LEFT && direction == RIGHT) {
    return true;
  }
  else if (head->direction->dir == RIGHT && direction == LEFT) {
    return true;
  }
  else {
    return false;
  }
}
  
void Quit(int reason, WINDOW *border, struct snakeNode *dead) {
  WINDOW *endGameWindow = newwin(10, 25, 20, COLS / 3 + 20);
  box(endGameWindow, 0, 0);

  mvwprintw(endGameWindow, 2, 3, "You hit something!");
  mvwprintw(endGameWindow, 4, 3, "Score: %d", dead->score);
  wrefresh(endGameWindow);
  wrefresh(border);
  refresh();
}
  
