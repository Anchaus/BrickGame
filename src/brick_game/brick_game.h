#ifndef BRICK_GAME_BRICK_GAME_H
#define BRICK_GAME_BRICK_GAME_H

#define ROWS_MAP 20
#define COLS_MAP 10

#define EMPTY 0
#define FILLED 1

#define ENTER 10
#define ESCAPE 27
#define SPACE 32

typedef enum {
  Start = 0,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  noAction
} UserAction_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

static GameInfo_t status;

#endif