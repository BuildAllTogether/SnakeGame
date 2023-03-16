
#define SNAKEHEADSTART 'd'
#define SNAKEBODY 'O'
#define FOOD 'X'
#define BASESPEED 50000

void Setup(void);
void PrintGameName(WINDOW *win, int startRow);
void InitSnake(void);
void ChangeDirection(chtype direction);
