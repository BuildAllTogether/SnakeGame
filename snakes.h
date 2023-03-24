#include <unistd.h>
#define SNAKEHEADSTART 'd'
#define SNAKEBODY 'o'
#define BASESPEED 200000

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4



struct snakeNode {
  int direction;
  int bufferDirection;
  int x;
  int y;
  int speed; // in microseconds
  struct snakeNode *next;
  WINDOW *border;
  int score;
  bool alive;
};

struct snakeNode* InitSnake(WINDOW *border);
void ChangeDirection(int direction, struct snakeNode *head);
void MoveSnake(struct snakeNode *head);
struct snakeNode* GetTail(struct snakeNode *head);
void ShiftLocation(struct snakeNode *head, int nextX, int nextY);
void ShiftLocationNotTail(struct snakeNode *head, int nextX, int nextY);
void IncreaseBody(struct snakeNode *head);
void *movementThread(void *arg);
void checkDirection(struct snakeNode *head);



