
#define SNAKEHEADSTART 'd'
#define SNAKEBODY 'O'
#define FOOD 'X'
#define BASESPEED 50000

struct snakeNode {
  chtype direction;
  struct snakeNode *next;
};

void Setup(void);
void PrintGameName(WINDOW *win, int startRow);
struct snakeNode* InitSnake(void);
void ChangeDirection(chtype direction, struct snakeNode *head);


