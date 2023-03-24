#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <pthread.h>

#include "snakes.h"
#include "food.h"
#include "board.h"

int main(int argc, char *argv[]) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(0);
  WINDOW *border = Setup();
  struct snakeNode *head = InitSnake(border);
  
  /* pthread_t movement; */
  /* pthread_create(&movement, NULL, &movementThread, head); */
   
  while(1) {
    int key = getch();

    switch(key) {
    case KEY_UP:
      ChangeDirection(UP, head);
      break;
    case KEY_DOWN:
      ChangeDirection(DOWN, head);
      break;
    case KEY_LEFT:
      ChangeDirection(LEFT, head);
      break;
    case KEY_RIGHT:
      ChangeDirection(RIGHT, head);
      break;
    case 'q':
      break;
    }
  }
  

  return 0;
}

