#ifndef BRICK_GAME_TETRIS_INC_FSM_H
#define BRICK_GAME_TETRIS_INC_FSM_H

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef __USE_MISC
#define __USE_MISC
#endif

#include <unistd.h>

#include "../../brick_game.h"
#include "defines.h"
#include "objects.h"

typedef enum {
  StartGame = 0,
  Spawn,
  Moving,
  Shifting,
  Attaching,
  GameOver,
  PauseGame
} GameState_t;

static GameState_t state;
static Figure_t moving_figure;

bool initGame();

void endGame();

void initMovingFigure(int size, int **blocks);

void deleteMovingFigure();

GameInfo_t updateCurrentState();

GameState_t updateStateInfo();

Figure_t updateFigureInfo();

UserAction_t getUserAction(UserAction_t prev_action, int user_input,
                           bool *hold);

void userInput(UserAction_t action, bool hold);

void onStartState(UserAction_t action);

void onMovingState(UserAction_t action, bool hold);

void onPauseState(UserAction_t action, bool hold);

void spawn();

void chooseFigure(int **blocks, int num);

void shuffle(int *array, size_t n);

void moving(int direction);

void spin();

void updateMap();

void deleteLines();

bool checkWallCollision(Figure_t figure);

bool checkObjectCollision(Figure_t figure);

bool checkAttach();

bool checkGameOver();

void _fieldEditor(int new_field[ROWS_MAP][COLS_MAP]);

void _figureCoordinatesEditor(int x, int y);

void freeField(int **field);

void freeNext(int **next);

#endif