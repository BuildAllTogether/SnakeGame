#include <unistd.h>

#define SNAKEHEADSTART 'd'
#define SNAKEBODY 'o'
#define BASESPEED 250000

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


struct direction {
  int dir;
  struct direction *next;
};


struct snakeNode {
  struct direction *direction;
  int bufferDirection;
  int x;
  int y;
  int speed; // in microseconds
  struct snakeNode *next;
  WINDOW *border;
  int score;
  bool alive;
  WINDOW *scoreWindow;
};

struct allwindows {
  WINDOW *board;
  WINDOW *name;
  WINDOW *score;
};

struct snakeNode *InitSnake(struct allwindows *allWindows);
void ChangeDirection(int direction, struct snakeNode *head);
void RemoveDirection(struct snakeNode *head);
int DirectionLength(struct direction *direction);
void MoveSnake(struct snakeNode *head);
struct snakeNode* GetSnakeTail(struct snakeNode *head);
struct direction *GetDirectionTail(struct direction *direction);
void ShiftLocation(struct snakeNode *head, int nextX, int nextY);
void ShiftLocationNotTail(struct snakeNode *head, int nextX, int nextY);
void IncreaseBody(struct snakeNode *head);
void *movementThread(void *arg);
void checkDirection(struct snakeNode *head);
bool NotLongerThan(struct direction *head, int length);
bool IsOpposite(struct snakeNode *head, int direction);
void Quit(int reason, WINDOW *border, struct snakeNode *dead);

