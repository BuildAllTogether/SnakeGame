
#define SNAKEHEADSTART 'd'
#define SNAKEBODY 'O'
#define FOOD 'X'
#define BASESPEED 500000

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
};

void Setup(void);
void PrintGameName(WINDOW *win, int startRow);
struct snakeNode* InitSnake(void);
void ChangeDirection(int direction, struct snakeNode *head);
void MoveSnake(struct snakeNode *head);
void *movementThread(void *arg);



