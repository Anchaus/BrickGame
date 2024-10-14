#include "../inc/fsm.h"

bool initGame() {
  bool error_flag = false;
  status.field = malloc(ROWS_MAP * sizeof(int *));

  for (int i = 0; i < ROWS_MAP; i++) {
    status.field[i] = malloc(COLS_MAP * sizeof(int));
    for (int j = 0; j < COLS_MAP; j++) {
      status.field[i][j] = 0;
    }
  }

  status.next = NULL;
  status.score = 0;

  char path[100] = "\0";
  strcpy(path, getenv("HOME"));
  strcat(path, "/.tetris/highscore.txt");

  FILE *file = fopen(path, "r");
  if (file) {
    fscanf(file, "%d", &status.high_score);
    fclose(file);
  } else
    error_flag = true;

  status.level = 0;
  status.speed = 48;
  status.pause = 0;

  moving_figure.blocks = NULL;

  state = StartGame;

  return error_flag;
}

void endGame() {
  for (int i = 0; i < ROWS_MAP; i++) free(status.field[i]);
  free(status.field);
  status.field = NULL;

  if (status.next != NULL) {
    for (int i = 0; i < moving_figure.next_size; i++) free(status.next[i]);
    free(status.next);
    status.next = NULL;
  }

  char path[100] = "\0";
  strcpy(path, getenv("HOME"));
  strcat(path, "/tetris/highscore.txt");

  FILE *file = fopen(path, "w");
  if (file) {
    fprintf(file, "%d", status.high_score);
    fclose(file);
  }

  if (moving_figure.blocks != NULL) {
    deleteMovingFigure();
    moving_figure.blocks = NULL;
  }
}

void initMovingFigure(int size, int **blocks) {
  moving_figure.size = size;
  moving_figure.x = COLS_MAP / 2 - (size > 2 ? 2 : 1);
  moving_figure.y = -2;

  if (blocks == NULL) {
    moving_figure.blocks = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
      moving_figure.blocks[i] = malloc(size * sizeof(int));
  } else
    moving_figure.blocks = blocks;
}

void deleteMovingFigure() {
  for (int i = 0; i < moving_figure.size; i++) free(moving_figure.blocks[i]);
  free(moving_figure.blocks);

  moving_figure.size = moving_figure.next_size;
  moving_figure.x = COLS_MAP / 2 - (moving_figure.size > 2 ? 2 : 1);
  moving_figure.y = -2;
}

GameInfo_t updateCurrentState() {
  GameInfo_t external_status;

  if (status.field != NULL) {
    external_status.field = malloc(ROWS_MAP * sizeof(int *));
    for (int i = 0; i < ROWS_MAP; i++) {
      external_status.field[i] = malloc(COLS_MAP * sizeof(int));
      for (int j = 0; j < COLS_MAP; j++)
        external_status.field[i][j] = status.field[i][j];
    }
  } else
    external_status.field = NULL;

  if (moving_figure.blocks != NULL && external_status.field != NULL) {
    for (int i = 0; i < moving_figure.size; i++) {
      int y = i + moving_figure.y;
      if (y < 0 || y >= ROWS_MAP) continue;
      for (int j = 0; j < moving_figure.size; j++) {
        int x = j + moving_figure.x;
        if (x < 0 || x >= COLS_MAP) continue;
        if (moving_figure.blocks[i][j]) external_status.field[y][x] = 1;
      }
    }
  }

  if (status.next != NULL) {
    external_status.next = malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; i++) {
      external_status.next[i] = malloc(4 * sizeof(int));
      for (int j = 0; j < 4; j++) external_status.next[i][j] = 0;
    }

    for (int i = 0; i < moving_figure.next_size; i++)
      for (int j = 0; j < moving_figure.next_size; j++)
        external_status.next[i][j] = status.next[i][j];
  } else
    external_status.next = NULL;

  external_status.score = status.score;
  external_status.high_score = status.high_score;
  external_status.level = status.level;
  external_status.speed = status.speed;
  external_status.pause = status.pause;

  return external_status;
}

GameState_t updateStateInfo() { return state; }

Figure_t updateFigureInfo() { return moving_figure; }

UserAction_t getUserAction(UserAction_t prev_action, int user_input,
                           bool *hold) {
  UserAction_t action = 0;

  switch (user_input) {
    case ENTER:
      action = Start;
      break;
    case 'p':
    case 'P':
      action = Pause;
      break;
    case ESCAPE:
      action = Terminate;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_UP:
      action = Up;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case SPACE:
      action = Action;
      break;
    default:
      action = noAction;
  }

  if (prev_action == action && action != noAction)
    *hold = true;
  else
    *hold = false;

  return action;
}

void userInput(UserAction_t action, bool hold) {
  switch (state) {
    case StartGame:
      onStartState(action);
      break;
    case Spawn:
      spawn();
      state = Moving;
      break;
    case Moving:
      onMovingState(action, hold);
      break;
    case Shifting:
      if (checkAttach())
        state = Attaching;
      else {
        moving_figure.y++;
        state = Moving;
      }
      break;
    case Attaching:
      if (checkGameOver())
        state = GameOver;
      else {
        updateMap();
        deleteLines();
        state = Spawn;
      }
      break;
    case GameOver:
      if (action == Start) state = StartGame;
      break;
    case PauseGame:
      onPauseState(action, hold);
      break;
  }
}

void onStartState(UserAction_t action) {
  switch (action) {
    case Start:
      state = Spawn;
      break;
    case Terminate:
      state = GameOver;
      break;
    default:
      state = StartGame;
  }
}

void onMovingState(UserAction_t action, bool hold) {
  static bool prev_shift_update = true;
  static clock_t prev_shift;

  if (prev_shift_update) {
    prev_shift = clock();
    prev_shift_update = false;
  }

  switch (action) {
    case Pause:
      status.pause = 1;
      state = PauseGame;
      break;
    case Terminate:
      state = GameOver;
      break;
    case Left:
      if (hold) usleep(10);
      moving(LEFT);
      break;
    case Right:
      if (hold) usleep(10);
      moving(RIGHT);
      break;
    case Down:
      if (hold) usleep(10);
      state = Shifting;
      break;
    case Action:
      spin();
      break;
    default:
      state = Moving;
  }

  double time_after_shift =
      (double)(clock() - prev_shift) / CLOCKS_PER_SEC * 30;
  double timeout = (double)status.speed / 60;

  if ((state == Moving && time_after_shift > timeout) || state == Shifting) {
    state = Shifting;
    prev_shift_update = true;
  }
}

void onPauseState(UserAction_t action, bool hold) {
  switch (action) {
    case Start:
    case Pause:
      status.pause = 0;
      state = Moving;
      break;
    case Terminate:
      state = GameOver;
      break;
    default:
      state = PauseGame;
  }
}

void spawn() {
  static int bag[7] = {0, 1, 2, 3, 4, 5, 6};
  static int bag_count = 6;

  if (bag_count > 6) {
    shuffle(bag, 7);
    bag_count = 0;
  }

  int **blocks = NULL;
  int size = bag[bag_count] == 0 ? 2 : bag[bag_count] == 6 ? 4 : 3;

  blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) blocks[i] = malloc(size * sizeof(int));

  chooseFigure(blocks, bag[bag_count]);
  bag_count++;

  if (status.next == NULL) {
    if (bag_count > 6) {
      shuffle(bag, 7);
      bag_count = 0;
    }
    initMovingFigure(size, blocks);

    int **next_blocks = NULL;
    int next_size = bag[bag_count] == 0 ? 2 : bag[bag_count] == 6 ? 4 : 3;

    next_blocks = malloc(next_size * sizeof(int *));
    for (int i = 0; i < next_size; i++)
      next_blocks[i] = malloc(next_size * sizeof(int));

    chooseFigure(next_blocks, bag[bag_count]);
    bag_count++;

    moving_figure.next_size = next_size;
    status.next = next_blocks;
  } else {
    deleteMovingFigure();
    moving_figure.blocks = status.next;
    moving_figure.next_size = size;
    status.next = blocks;
  }
}

void chooseFigure(int **blocks, int num) {
  int size = 0;

  if (num == 0) {
    int fig[2][2] = FIGURE_1;
    size = 2;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) blocks[i][j] = fig[i][j];
  } else if (num == 1) {
    int fig[3][3] = FIGURE_2;
    size = 3;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) blocks[i][j] = fig[i][j];
  } else if (num == 2) {
    int fig[3][3] = FIGURE_3;
    size = 3;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) blocks[i][j] = fig[i][j];
  } else if (num == 3) {
    int fig[3][3] = FIGURE_4;
    size = 3;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) blocks[i][j] = fig[i][j];
  } else if (num == 4) {
    int fig[3][3] = FIGURE_5;
    size = 3;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) blocks[i][j] = fig[i][j];
  } else if (num == 5) {
    int fig[3][3] = FIGURE_6;
    size = 3;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) blocks[i][j] = fig[i][j];
  } else if (num == 6) {
    int fig[4][4] = FIGURE_7;
    size = 4;
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) blocks[i][j] = fig[i][j];
  }
}

void shuffle(int *array, size_t n) {
  if (n > 1) {
    size_t i;
    srand(time(NULL));
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

void moving(int direction) {
  int size = moving_figure.size;
  Figure_t temp;
  temp.size = size;
  temp.y = moving_figure.y;
  temp.x = moving_figure.x + (direction ? 1 : -1);
  temp.blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    temp.blocks[i] = malloc(size * sizeof(int));
    for (int j = 0; j < size; j++)
      temp.blocks[i][j] = moving_figure.blocks[i][j];
  }

  if (!checkWallCollision(temp) && !checkObjectCollision(temp)) {
    for (int i = 0; i < size; i++) free(moving_figure.blocks[i]);
    free(moving_figure.blocks);
    moving_figure.blocks = temp.blocks;
    moving_figure.x = temp.x;
  } else {
    for (int i = 0; i < size; i++) free(temp.blocks[i]);
    free(temp.blocks);
  }
}

void spin() {
  if (moving_figure.size == 2 ||
      moving_figure.y + moving_figure.size > ROWS_MAP)
    return;

  int size = moving_figure.size;
  Figure_t temp;
  temp.size = size;
  temp.x = moving_figure.x;
  temp.y = moving_figure.y;
  temp.blocks = malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) temp.blocks[i] = malloc(size * sizeof(int));

  if (moving_figure.x < 0) temp.x = 0;
  if (moving_figure.x + size > COLS_MAP) temp.x = COLS_MAP - size;

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      temp.blocks[j][size - i - 1] = moving_figure.blocks[i][j];
    }
  }

  if (!checkObjectCollision(temp)) {
    for (int i = 0; i < size; i++) free(moving_figure.blocks[i]);
    free(moving_figure.blocks);
    moving_figure.blocks = temp.blocks;
    moving_figure.x = temp.x;
  } else {
    for (int i = 0; i < temp.size; i++) free(temp.blocks[i]);
    free(temp.blocks);
  }
}

void updateMap() {
  for (int i = 0, y = moving_figure.y; i < moving_figure.size; i++, y++) {
    if (y < 0 || y >= ROWS_MAP) continue;
    for (int j = 0, x = moving_figure.x; j < moving_figure.size; j++, x++) {
      if (x < 0 || x >= COLS_MAP) continue;
      if (moving_figure.blocks[i][j]) status.field[y][x] = 1;
    }
  }
}

void deleteLines() {
  int lines_count = 0;

  for (int i = ROWS_MAP - 1; i >= 0; i--) {
    int j = 0;
    for (; j < COLS_MAP && status.field[i][j]; j++)
      ;
    if (j == COLS_MAP) {
      lines_count++;
      for (int row = i; row > 0; row--)
        for (int col = 0; col < COLS_MAP; col++)
          status.field[row][col] = status.field[row - 1][col];
      for (int col = 0; col < COLS_MAP; col++) status.field[0][col] = 0;
      i++;
    }
  }

  switch (lines_count) {
    case 1:
      status.score += 100;
      break;
    case 2:
      status.score += 300;
      break;
    case 3:
      status.score += 700;
      break;
    case 4:
      status.score += 1500;
  }

  while (status.score >= (status.level + 1) * 600 && status.level < 10) {
    status.level++;
    if (status.level < 8)
      status.speed -= 5;
    else if (status.level == 8)
      status.speed -= 2;
    else if (status.level == 9)
      status.speed -= 1;
  }

  if (status.score > status.high_score) status.high_score = status.score;
}

bool checkWallCollision(Figure_t figure) {
  bool collision_flag = false;
  int size = figure.size;

  if (figure.x < 0) {
    for (int x = figure.x, i = 0; x < 0; x++, i++)
      for (int j = 0; j < size; j++)
        if (figure.blocks[j][i]) collision_flag = true;
  } else if (figure.x + size > COLS_MAP) {
    for (int x = figure.x + size - 1, i = size - 1; x >= COLS_MAP; x--, i--)
      for (int j = 0; j < size; j++)
        if (figure.blocks[j][i]) collision_flag = true;
  }

  return collision_flag;
}

bool checkObjectCollision(Figure_t figure) {
  bool collision_flag = false;

  for (int y = figure.y, i = 0; i < figure.size; y++, i++) {
    if (y < 0) continue;
    for (int x = figure.x, j = 0; j < figure.size; x++, j++) {
      if (x < 0 || x >= COLS_MAP) continue;
      if (y >= ROWS_MAP) {
        if (figure.blocks[i][j]) collision_flag = true;
      } else if (status.field[y][x] && figure.blocks[i][j])
        collision_flag = true;
    }
  }

  return collision_flag;
}

bool checkAttach() {
  bool attach_flag = false;

  for (int row = moving_figure.size - 1;
       row >= 0 && moving_figure.y + row + 1 >= 0 && attach_flag == false;
       row--) {
    for (int col = 0; col < moving_figure.size && attach_flag == false; col++) {
      if (moving_figure.blocks[row][col]) {
        if (moving_figure.y + row + 1 == ROWS_MAP)
          attach_flag = true;
        else if (status.field[moving_figure.y + row + 1][moving_figure.x + col])
          attach_flag = true;
      }
    }
  }

  return attach_flag;
}

bool checkGameOver() {
  bool gameover_flag = false;
  int y = moving_figure.y;
  int size = moving_figure.size;

  if (y < 0) {
    for (int col = 0; col < size; col++)
      if (moving_figure.blocks[-y - 1][col]) gameover_flag = true;
  }

  return gameover_flag;
}

void _fieldEditor(int new_field[ROWS_MAP][COLS_MAP]) {
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++) status.field[i][j] = new_field[i][j];
}

void _figureCoordinatesEditor(int x, int y) {
  if (x != NOT_EDIT) moving_figure.x = x;
  if (y != NOT_EDIT) moving_figure.y = y;
}

void freeField(int **field) {
  if (field != NULL) {
    for (int i = 0; i < ROWS_MAP; i++) free(field[i]);
    free(field);
  }
}

void freeNext(int **next) {
  if (next != NULL) {
    for (int i = 0; i < 4; i++) free(next[i]);
    free(next);
  }
}