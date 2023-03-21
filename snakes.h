
#define SNAKEHEADSTART 'd'
#define SNAKEBODY 'O'
#define BASESPEED 200000

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

struct snakeNode {
  int direction;
  int x;
  int y;
  int speed; // in microseconds
  struct snakeNode *next;
  WINDOW *border;
};

struct snakeNode* InitSnake(WINDOW *border);
void ChangeDirection(int direction, struct snakeNode *head);
void MoveSnake(struct snakeNode *head);
void *movementThread(void *arg);



