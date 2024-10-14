#include "unit_test.h"

////////////////////
// init game test //
////////////////////

START_TEST(initGame_1) {
  initGame();

  GameInfo_t status = updateCurrentState();
  GameState_t game_state = updateStateInfo();

  ck_assert_int_eq(status.level, 0);
  ck_assert_int_eq(status.pause, 0);
  ck_assert_int_eq(status.score, 0);
  ck_assert_int_eq(game_state, 0);
  ck_assert_ptr_null(status.next);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}

///////////////////////
// Init figure tests //
///////////////////////

START_TEST(initMovingFigure_1) {
  initMovingFigure(2, NULL);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(figure.size, 2);
  ck_assert_int_eq(figure.x, 4);
  ck_assert_int_eq(figure.y, -2);

  deleteMovingFigure();
}
END_TEST

START_TEST(initMovingFigure_2) {
  initMovingFigure(3, NULL);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(figure.size, 3);
  ck_assert_int_eq(figure.x, 3);
  ck_assert_int_eq(figure.y, -2);

  deleteMovingFigure();
}
END_TEST

START_TEST(initMovingFigure_3) {
  initMovingFigure(4, NULL);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(figure.size, 4);
  ck_assert_int_eq(figure.x, 3);
  ck_assert_int_eq(figure.y, -2);

  deleteMovingFigure();
}
END_TEST

START_TEST(initMovingFigure_4) {
  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  initMovingFigure(3, blocks);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(figure.size, 3);
  ck_assert_int_eq(figure.x, 3);
  ck_assert_int_eq(figure.y, -2);

  deleteMovingFigure();
}

///////////////////////////
// Get user action tests //
///////////////////////////

START_TEST(getUserAction_1) {
  bool hold = false;
  UserAction_t action = getUserAction(0, ENTER, &hold);

  ck_assert_int_eq(action, 0);
  ck_assert_int_eq(hold, 1);
}
END_TEST

START_TEST(getUserAction_2) {
  bool hold = false;
  UserAction_t action = getUserAction(1, ENTER, &hold);

  ck_assert_int_eq(action, 0);
  ck_assert_int_eq(hold, 0);
}
END_TEST

START_TEST(getUserAction_3) {
  bool hold = false;
  UserAction_t action = getUserAction(0, KEY_LEFT, &hold);

  ck_assert_int_eq(action, 3);
  ck_assert_int_eq(hold, 0);
}
END_TEST

START_TEST(getUserAction_4) {
  bool hold = false;
  UserAction_t action = getUserAction(0, 65, &hold);

  ck_assert_int_eq(action, 8);
  ck_assert_int_eq(hold, 0);
}
END_TEST

START_TEST(getUserAction_5) {
  bool hold = false;
  UserAction_t action = getUserAction(0, 'p', &hold);

  ck_assert_int_eq(action, 1);
  ck_assert_int_eq(hold, 0);
}
END_TEST

START_TEST(getUserAction_6) {
  bool hold = false;
  UserAction_t action = getUserAction(0, ESCAPE, &hold);

  ck_assert_int_eq(action, 2);
  ck_assert_int_eq(hold, 0);
}
END_TEST

START_TEST(getUserAction_7) {
  bool hold = false;
  UserAction_t action = getUserAction(0, KEY_RIGHT, &hold);

  ck_assert_int_eq(action, 4);
  ck_assert_int_eq(hold, 0);
}
END_TEST

START_TEST(getUserAction_8) {
  bool hold = false;
  UserAction_t action = getUserAction(0, KEY_UP, &hold);

  ck_assert_int_eq(action, 5);
  ck_assert_int_eq(hold, 0);
}
END_TEST

START_TEST(getUserAction_9) {
  bool hold = false;
  UserAction_t action = getUserAction(0, KEY_DOWN, &hold);

  ck_assert_int_eq(action, 6);
  ck_assert_int_eq(hold, 0);
}
END_TEST

START_TEST(getUserAction_10) {
  bool hold = false;
  UserAction_t action = getUserAction(0, SPACE, &hold);

  ck_assert_int_eq(action, 7);
  ck_assert_int_eq(hold, 0);
}
END_TEST

//////////////////////////
// On start state tests //
//////////////////////////

START_TEST(onStartState_1) {
  initGame();

  onStartState(0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 1);

  endGame();
}
END_TEST

START_TEST(onStartState_2) {
  initGame();

  onStartState(2);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 5);

  endGame();
}
END_TEST

START_TEST(onStartState_3) {
  initGame();

  onStartState(6);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 0);

  endGame();
}
END_TEST

/////////////////////////
// onMovingState tests //
/////////////////////////

START_TEST(onMovingState_1) {
  initGame();

  onMovingState(1, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 6);

  endGame();
}
END_TEST

START_TEST(onMovingState_2) {
  initGame();

  onMovingState(2, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 5);

  endGame();
}
END_TEST

START_TEST(onMovingState_3) {
  initGame();
  initMovingFigure(3, NULL);

  onMovingState(3, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 0);

  endGame();
}
END_TEST

START_TEST(onMovingState_4) {
  initGame();
  initMovingFigure(3, NULL);

  onMovingState(4, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 0);

  endGame();
}
END_TEST

START_TEST(onMovingState_5) {
  initGame();

  onMovingState(6, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 3);

  endGame();
}
END_TEST

START_TEST(onMovingState_6) {
  initGame();
  initMovingFigure(3, NULL);

  onMovingState(7, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 0);

  endGame();
}
END_TEST

START_TEST(onMovingState_7) {
  initGame();

  onMovingState(8, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 2);

  endGame();
}
END_TEST

////////////////////////
// onPauseState tests //
////////////////////////

START_TEST(onPauseState_1) {
  initGame();

  onPauseState(0, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 2);

  endGame();
}

START_TEST(onPauseState_2) {
  initGame();

  onPauseState(2, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 5);

  endGame();
}

START_TEST(onPauseState_3) {
  initGame();

  onPauseState(7, 0);
  GameState_t game_state = updateStateInfo();
  ck_assert_int_eq(game_state, 6);

  endGame();
}

/////////////////
// spawn tests //
/////////////////

START_TEST(spawn_1) {
  initGame();
  spawn();

  GameInfo_t status = updateCurrentState();
  ck_assert_ptr_nonnull(status.next);

  Figure_t figure = updateFigureInfo();
  ck_assert_ptr_nonnull(figure.blocks);

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }

  spawn();

  status = updateCurrentState();
  ck_assert_ptr_nonnull(status.next);

  figure = updateFigureInfo();
  ck_assert_ptr_nonnull(figure.blocks);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}

START_TEST(spawn_2) {
  initGame();
  spawn();
  spawn();
  spawn();
  spawn();
  spawn();
  spawn();
  spawn();
  spawn();

  GameInfo_t status = updateCurrentState();
  ck_assert_ptr_nonnull(status.next);

  Figure_t figure = updateFigureInfo();
  ck_assert_ptr_nonnull(figure.blocks);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}

////////////////////////
// chooseFigure tests //
////////////////////////

START_TEST(chooseFigure_1) {
  int size = 2;
  int **result = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) result[i] = malloc(size * sizeof(int));

  int expected[2][2] = FIGURE_1;
  chooseFigure(result, 0);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(result[i][j], expected[i][j]);

  for (int i = 0; i < size; i++) free(result[i]);
  free(result);
}
END_TEST

START_TEST(chooseFigure_2) {
  int size = 3;
  int **result = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) result[i] = malloc(size * sizeof(int));

  int expected[3][3] = FIGURE_2;
  chooseFigure(result, 1);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(result[i][j], expected[i][j]);

  for (int i = 0; i < size; i++) free(result[i]);
  free(result);
}
END_TEST

START_TEST(chooseFigure_3) {
  int size = 3;
  int **result = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) result[i] = malloc(size * sizeof(int));

  int expected[3][3] = FIGURE_3;
  chooseFigure(result, 2);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(result[i][j], expected[i][j]);

  for (int i = 0; i < size; i++) free(result[i]);
  free(result);
}
END_TEST

START_TEST(chooseFigure_4) {
  int size = 3;
  int **result = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) result[i] = malloc(size * sizeof(int));

  int expected[3][3] = FIGURE_4;
  chooseFigure(result, 3);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(result[i][j], expected[i][j]);

  for (int i = 0; i < size; i++) free(result[i]);
  free(result);
}
END_TEST

START_TEST(chooseFigure_5) {
  int size = 3;
  int **result = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) result[i] = malloc(size * sizeof(int));

  int expected[3][3] = FIGURE_5;
  chooseFigure(result, 4);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(result[i][j], expected[i][j]);

  for (int i = 0; i < size; i++) free(result[i]);
  free(result);
}
END_TEST

START_TEST(chooseFigure_6) {
  int size = 3;
  int **result = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) result[i] = malloc(size * sizeof(int));

  int expected[3][3] = FIGURE_6;
  chooseFigure(result, 5);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(result[i][j], expected[i][j]);

  for (int i = 0; i < size; i++) free(result[i]);
  free(result);
}
END_TEST

START_TEST(chooseFigure_7) {
  int size = 4;
  int **result = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) result[i] = malloc(size * sizeof(int));

  int expected[4][4] = FIGURE_7;
  chooseFigure(result, 6);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(result[i][j], expected[i][j]);

  for (int i = 0; i < size; i++) free(result[i]);
  free(result);
}
END_TEST

//////////////////////////////
// checkWallCollision tests //
//////////////////////////////

START_TEST(checkWallCollision_1) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(checkWallCollision(figure), false);

  endGame();
}
END_TEST

START_TEST(checkWallCollision_2) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(-1, NOT_EDIT);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(checkWallCollision(figure), true);

  endGame();
}
END_TEST

START_TEST(checkWallCollision_3) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(8, NOT_EDIT);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(checkWallCollision(figure), true);

  endGame();
}
END_TEST

START_TEST(checkWallCollision_4) {
  initGame();

  int fig[3][3] = {{0, 1, 1}, {0, 1, 0}, {0, 1, 0}};

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    blocks[i] = malloc(3 * sizeof(int));
    for (int j = 0; j < 3; j++) blocks[i][j] = fig[i][j];
  }

  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(-1, NOT_EDIT);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(checkWallCollision(figure), false);

  endGame();
}
END_TEST

START_TEST(checkWallCollision_5) {
  initGame();

  int fig[3][3] = {{0, 1, 0}, {0, 1, 0}, {1, 1, 0}};

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) {
    blocks[i] = malloc(3 * sizeof(int));
    for (int j = 0; j < 3; j++) blocks[i][j] = fig[i][j];
  }

  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(8, NOT_EDIT);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(checkWallCollision(figure), false);

  endGame();
}
END_TEST

START_TEST(checkWallCollision_6) {
  initGame();

  int fig[4][4] = {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};

  int **blocks = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    blocks[i] = malloc(4 * sizeof(int));
    for (int j = 0; j < 4; j++) blocks[i][j] = fig[i][j];
  }

  initMovingFigure(4, blocks);
  _figureCoordinatesEditor(8, NOT_EDIT);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(checkWallCollision(figure), false);

  endGame();
}
END_TEST

START_TEST(checkWallCollision_7) {
  initGame();

  int fig[4][4] = {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}};

  int **blocks = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) {
    blocks[i] = malloc(4 * sizeof(int));
    for (int j = 0; j < 4; j++) blocks[i][j] = fig[i][j];
  }

  initMovingFigure(4, blocks);
  _figureCoordinatesEditor(9, NOT_EDIT);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(checkWallCollision(figure), true);

  endGame();
}
END_TEST

////////////////////////////////
// checkObjectCollision tests //
////////////////////////////////

START_TEST(checkObjectCollision_1) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(checkObjectCollision(figure), false);

  endGame();
}
END_TEST

START_TEST(checkObjectCollision_2) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(NOT_EDIT, ROWS_MAP - 1);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(checkObjectCollision(figure), true);

  endGame();
}
END_TEST

START_TEST(checkObjectCollision_3) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(NOT_EDIT, ROWS_MAP - 2);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(checkObjectCollision(figure), false);

  endGame();
}
END_TEST

START_TEST(checkObjectCollision_4) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  _fieldEditor(new_map);

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(0, ROWS_MAP - 3);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(checkObjectCollision(figure), true);

  endGame();
}
END_TEST

START_TEST(checkObjectCollision_5) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  _fieldEditor(new_map);

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(2, ROWS_MAP - 4);

  Figure_t figure = updateFigureInfo();

  ck_assert_int_eq(checkObjectCollision(figure), true);

  endGame();
}
END_TEST

///////////////////////
// checkAttach tests //
///////////////////////

START_TEST(checkAttach_1) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);

  ck_assert_int_eq(checkAttach(), false);

  endGame();
}
END_TEST

START_TEST(checkAttach_2) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(NOT_EDIT, ROWS_MAP - 2);

  ck_assert_int_eq(checkAttach(), true);

  endGame();
}
END_TEST

START_TEST(checkAttach_3) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  _fieldEditor(new_map);

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(0, 15);

  ck_assert_int_eq(checkAttach(), true);

  endGame();
}
END_TEST

START_TEST(checkAttach_4) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  _fieldEditor(new_map);

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(0, 13);

  ck_assert_int_eq(checkAttach(), false);

  endGame();
}
END_TEST

/////////////////////////
// checkGameOver tests //
/////////////////////////

START_TEST(checkGameOver_1) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(NOT_EDIT, 0);

  ck_assert_int_eq(checkGameOver(), false);

  endGame();
}

START_TEST(checkGameOver_2) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);
  _figureCoordinatesEditor(NOT_EDIT, -1);

  ck_assert_int_eq(checkGameOver(), true);

  endGame();
}

START_TEST(checkGameOver_3) {
  initGame();

  int **blocks = malloc(4 * sizeof(int *));
  for (int i = 0; i < 4; i++) blocks[i] = malloc(4 * sizeof(int));

  chooseFigure(blocks, 6);
  initMovingFigure(4, blocks);
  _figureCoordinatesEditor(NOT_EDIT, -1);

  ck_assert_int_eq(checkGameOver(), false);

  endGame();
}

//////////////////
// moving tests //
//////////////////

START_TEST(moving_1) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);

  Figure_t figure = updateFigureInfo();
  int expected = figure.x - 1;

  moving(LEFT);

  figure = updateFigureInfo();
  ck_assert_int_eq(figure.x, expected);

  endGame();
}
END_TEST

START_TEST(moving_2) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);

  Figure_t figure = updateFigureInfo();
  int expected = figure.x + 1;

  moving(RIGHT);

  figure = updateFigureInfo();
  ck_assert_int_eq(figure.x, expected);

  endGame();
}
END_TEST

START_TEST(moving_3) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);

  int expected = 0;

  moving(LEFT);
  moving(LEFT);
  moving(LEFT);
  moving(LEFT);
  moving(LEFT);
  moving(LEFT);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(figure.x, expected);

  endGame();
}
END_TEST

START_TEST(moving_4) {
  initGame();

  int **blocks = malloc(3 * sizeof(int *));
  for (int i = 0; i < 3; i++) blocks[i] = malloc(3 * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(3, blocks);

  int expected = COLS_MAP - 3;

  moving(RIGHT);
  moving(RIGHT);
  moving(RIGHT);
  moving(RIGHT);
  moving(RIGHT);
  moving(RIGHT);

  Figure_t figure = updateFigureInfo();
  ck_assert_int_eq(figure.x, expected);

  endGame();
}
END_TEST

////////////////
// spin tests //
////////////////

START_TEST(spin_1) {
  initGame();

  int size = 2;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 0);
  initMovingFigure(size, blocks);

  int expected[2][2] = FIGURE_1;

  spin();
  Figure_t figure = updateFigureInfo();

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(figure.blocks[i][j], expected[i][j]);

  endGame();
}
END_TEST

START_TEST(spin_2) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);

  int expected[3][3] = {{0, 1, 1}, {0, 1, 0}, {0, 1, 0}};

  spin();
  Figure_t figure = updateFigureInfo();

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(figure.blocks[i][j], expected[i][j]);

  endGame();
}
END_TEST

START_TEST(spin_3) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);

  int expected[3][3] = {{0, 0, 0}, {1, 1, 1}, {0, 0, 1}};

  spin();
  spin();
  Figure_t figure = updateFigureInfo();

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(figure.blocks[i][j], expected[i][j]);

  endGame();
}
END_TEST

START_TEST(spin_4) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);

  int expected[3][3] = {{0, 1, 0}, {0, 1, 0}, {1, 1, 0}};

  spin();
  spin();
  spin();
  Figure_t figure = updateFigureInfo();

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(figure.blocks[i][j], expected[i][j]);

  endGame();
}
END_TEST

START_TEST(spin_5) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);

  int expected[3][3] = FIGURE_2;

  spin();
  spin();
  spin();
  spin();
  Figure_t figure = updateFigureInfo();

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(figure.blocks[i][j], expected[i][j]);

  endGame();
}
END_TEST

START_TEST(spin_6) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);

  int expected[3][3] = {{0, 1, 1}, {0, 1, 0}, {0, 1, 0}};
  int expected_x = 0;

  _figureCoordinatesEditor(-1, NOT_EDIT);
  spin();
  Figure_t figure = updateFigureInfo();

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(figure.blocks[i][j], expected[i][j]);

  ck_assert_int_eq(figure.x, expected_x);

  endGame();
}
END_TEST

START_TEST(spin_7) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);

  int expected[3][3] = {{0, 1, 1}, {0, 1, 0}, {0, 1, 0}};
  int expected_x = 7;

  _figureCoordinatesEditor(8, NOT_EDIT);
  spin();
  Figure_t figure = updateFigureInfo();

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      ck_assert_int_eq(figure.blocks[i][j], expected[i][j]);

  ck_assert_int_eq(figure.x, expected_x);

  endGame();
}
END_TEST

/////////////////////
// updateMap tests //
/////////////////////

START_TEST(updateMap_1) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);
  _figureCoordinatesEditor(0, 0);

  int expected[ROWS_MAP][COLS_MAP] = {
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  updateMap();

  GameInfo_t status = updateCurrentState();
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      ck_assert_int_eq(status.field[i][j], expected[i][j]);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}
END_TEST

START_TEST(updateMap_2) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);
  _figureCoordinatesEditor(0, 18);

  int expected[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 0, 0, 0, 0, 0, 0, 0}};

  updateMap();

  GameInfo_t status = updateCurrentState();
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      ck_assert_int_eq(status.field[i][j], expected[i][j]);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}
END_TEST

START_TEST(updateMap_3) {
  initGame();

  int size = 3;
  int **blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, 1);
  initMovingFigure(size, blocks);
  spin();
  spin();
  spin();
  _figureCoordinatesEditor(8, 0);

  int expected[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  updateMap();

  GameInfo_t status = updateCurrentState();
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      ck_assert_int_eq(status.field[i][j], expected[i][j]);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}
END_TEST

///////////////////////
// deleteLines tests //
///////////////////////

START_TEST(deleteLines_1) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  _fieldEditor(new_map);
  deleteLines();

  int expected[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 1, 1, 1, 1, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}};
  int expected_score = 100;
  int expected_level = 0;

  GameInfo_t status = updateCurrentState();

  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      ck_assert_int_eq(status.field[i][j], expected[i][j]);
  ck_assert_int_eq(status.score, expected_score);
  ck_assert_int_eq(status.level, expected_level);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}
END_TEST

START_TEST(deleteLines_2) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  _fieldEditor(new_map);
  deleteLines();

  int expected[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0}};
  int expected_score = 300;
  int expected_level = 0;

  GameInfo_t status = updateCurrentState();

  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      ck_assert_int_eq(status.field[i][j], expected[i][j]);
  ck_assert_int_eq(status.score, expected_score);
  ck_assert_int_eq(status.level, expected_level);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}
END_TEST

START_TEST(deleteLines_3) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  _fieldEditor(new_map);
  deleteLines();

  int expected[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  int expected_score = 700;
  int expected_level = 1;

  GameInfo_t status = updateCurrentState();

  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      ck_assert_int_eq(status.field[i][j], expected[i][j]);
  ck_assert_int_eq(status.score, expected_score);
  ck_assert_int_eq(status.level, expected_level);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}
END_TEST

START_TEST(deleteLines_4) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

  _fieldEditor(new_map);
  deleteLines();

  int expected[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 1, 1, 0, 0, 0}};
  int expected_score = 1500;
  int expected_level = 2;

  GameInfo_t status = updateCurrentState();

  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      ck_assert_int_eq(status.field[i][j], expected[i][j]);
  ck_assert_int_eq(status.score, expected_score);
  ck_assert_int_eq(status.level, expected_level);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}
END_TEST

START_TEST(deleteLines_5) {
  initGame();

  int new_map[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1}};

  _fieldEditor(new_map);
  deleteLines();

  int expected[ROWS_MAP][COLS_MAP] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 1, 1, 1, 1, 0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 0, 1, 1}};
  int expected_score = 0;
  int expected_level = 0;

  GameInfo_t status = updateCurrentState();

  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      ck_assert_int_eq(status.field[i][j], expected[i][j]);
  ck_assert_int_eq(status.score, expected_score);
  ck_assert_int_eq(status.level, expected_level);

  endGame();

  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);

  if (status.next != NULL) {
    for (int i = 0; i < 4; i++) free(status.next[i]);
    free(status.next);
  }
}
END_TEST

Suite *fsm_suite(void) {
  Suite *suite = suite_create("FSM TEST");

  TCase *initGame_tc = tcase_create("initGame test");
  tcase_add_test(initGame_tc, initGame_1);

  TCase *initMovingFigure_tc = tcase_create("initMovingFigure tests");
  tcase_add_test(initMovingFigure_tc, initMovingFigure_1);
  tcase_add_test(initMovingFigure_tc, initMovingFigure_2);
  tcase_add_test(initMovingFigure_tc, initMovingFigure_3);
  tcase_add_test(initMovingFigure_tc, initMovingFigure_4);

  TCase *getUserAction_tc = tcase_create("getUserAction tests");
  tcase_add_test(getUserAction_tc, getUserAction_1);
  tcase_add_test(getUserAction_tc, getUserAction_2);
  tcase_add_test(getUserAction_tc, getUserAction_3);
  tcase_add_test(getUserAction_tc, getUserAction_4);
  tcase_add_test(getUserAction_tc, getUserAction_5);
  tcase_add_test(getUserAction_tc, getUserAction_6);
  tcase_add_test(getUserAction_tc, getUserAction_7);
  tcase_add_test(getUserAction_tc, getUserAction_8);
  tcase_add_test(getUserAction_tc, getUserAction_9);
  tcase_add_test(getUserAction_tc, getUserAction_10);

  TCase *onStartState_tc = tcase_create("onStartState tests");
  tcase_add_test(onStartState_tc, onStartState_1);
  tcase_add_test(onStartState_tc, onStartState_2);
  tcase_add_test(onStartState_tc, onStartState_3);

  TCase *onMovingState_tc = tcase_create("onMovingState tests");
  tcase_add_test(onMovingState_tc, onMovingState_1);
  tcase_add_test(onMovingState_tc, onMovingState_2);
  tcase_add_test(onMovingState_tc, onMovingState_3);
  tcase_add_test(onMovingState_tc, onMovingState_4);
  tcase_add_test(onMovingState_tc, onMovingState_5);
  tcase_add_test(onMovingState_tc, onMovingState_6);
  tcase_add_test(onMovingState_tc, onMovingState_7);

  TCase *onPauseState_tc = tcase_create("onPauseState tests");
  tcase_add_test(onPauseState_tc, onPauseState_1);
  tcase_add_test(onPauseState_tc, onPauseState_2);
  tcase_add_test(onPauseState_tc, onPauseState_3);

  TCase *spawn_tc = tcase_create("spawn tests");
  tcase_add_test(spawn_tc, spawn_1);
  tcase_add_test(spawn_tc, spawn_2);

  TCase *chooseFigure_tc = tcase_create("chooseFigure tests");
  tcase_add_test(chooseFigure_tc, chooseFigure_1);
  tcase_add_test(chooseFigure_tc, chooseFigure_2);
  tcase_add_test(chooseFigure_tc, chooseFigure_3);
  tcase_add_test(chooseFigure_tc, chooseFigure_4);
  tcase_add_test(chooseFigure_tc, chooseFigure_5);
  tcase_add_test(chooseFigure_tc, chooseFigure_6);
  tcase_add_test(chooseFigure_tc, chooseFigure_7);

  TCase *checkWallCollision_tc = tcase_create("checkWallCollision tests");
  tcase_add_test(checkWallCollision_tc, checkWallCollision_1);
  tcase_add_test(checkWallCollision_tc, checkWallCollision_2);
  tcase_add_test(checkWallCollision_tc, checkWallCollision_3);
  tcase_add_test(checkWallCollision_tc, checkWallCollision_4);
  tcase_add_test(checkWallCollision_tc, checkWallCollision_5);
  tcase_add_test(checkWallCollision_tc, checkWallCollision_6);
  tcase_add_test(checkWallCollision_tc, checkWallCollision_7);

  TCase *checkObjectCollision_tc = tcase_create("checkObjectCollision");
  tcase_add_test(checkObjectCollision_tc, checkObjectCollision_1);
  tcase_add_test(checkObjectCollision_tc, checkObjectCollision_2);
  tcase_add_test(checkObjectCollision_tc, checkObjectCollision_3);
  tcase_add_test(checkObjectCollision_tc, checkObjectCollision_4);
  tcase_add_test(checkObjectCollision_tc, checkObjectCollision_5);

  TCase *checkAttach_tc = tcase_create("checkAttach tests");
  tcase_add_test(checkAttach_tc, checkAttach_1);
  tcase_add_test(checkAttach_tc, checkAttach_2);
  tcase_add_test(checkAttach_tc, checkAttach_3);
  tcase_add_test(checkAttach_tc, checkAttach_4);

  TCase *checkGameOver_tc = tcase_create("checkGameOver tests");
  tcase_add_test(checkGameOver_tc, checkGameOver_1);
  tcase_add_test(checkGameOver_tc, checkGameOver_2);
  tcase_add_test(checkGameOver_tc, checkGameOver_3);

  TCase *moving_tc = tcase_create("moving tests");
  tcase_add_test(moving_tc, moving_1);
  tcase_add_test(moving_tc, moving_2);
  tcase_add_test(moving_tc, moving_3);
  tcase_add_test(moving_tc, moving_4);

  TCase *spin_tc = tcase_create("spin tests");
  tcase_add_test(spin_tc, spin_1);
  tcase_add_test(spin_tc, spin_2);
  tcase_add_test(spin_tc, spin_3);
  tcase_add_test(spin_tc, spin_4);
  tcase_add_test(spin_tc, spin_5);
  tcase_add_test(spin_tc, spin_6);
  tcase_add_test(spin_tc, spin_7);

  TCase *updateMap_tc = tcase_create("updateMap tests");
  tcase_add_test(updateMap_tc, updateMap_1);
  tcase_add_test(updateMap_tc, updateMap_2);
  tcase_add_test(updateMap_tc, updateMap_3);

  TCase *deleteLines_tc = tcase_create("deleteLines tests");
  tcase_add_test(deleteLines_tc, deleteLines_1);
  tcase_add_test(deleteLines_tc, deleteLines_2);
  tcase_add_test(deleteLines_tc, deleteLines_3);
  tcase_add_test(deleteLines_tc, deleteLines_4);
  tcase_add_test(deleteLines_tc, deleteLines_5);

  suite_add_tcase(suite, initGame_tc);
  suite_add_tcase(suite, initMovingFigure_tc);
  suite_add_tcase(suite, getUserAction_tc);
  suite_add_tcase(suite, onStartState_tc);
  suite_add_tcase(suite, onMovingState_tc);
  suite_add_tcase(suite, onPauseState_tc);
  suite_add_tcase(suite, spawn_tc);
  suite_add_tcase(suite, chooseFigure_tc);
  suite_add_tcase(suite, checkWallCollision_tc);
  suite_add_tcase(suite, checkObjectCollision_tc);
  suite_add_tcase(suite, checkAttach_tc);
  suite_add_tcase(suite, checkGameOver_tc);
  suite_add_tcase(suite, moving_tc);
  suite_add_tcase(suite, spin_tc);
  suite_add_tcase(suite, updateMap_tc);
  suite_add_tcase(suite, deleteLines_tc);

  return suite;
}