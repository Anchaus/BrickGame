#include "../inc/tetris.h"

int main() {
  initCli();
  bool error_flag = initGame();

  if (!error_flag) {
    GameInfo_t status = updateCurrentState();
    printInitScreen(status.high_score, "SPIN");
    gameLoop();

    freeField(status.field);
    freeNext(status.next);
  } else {
    timeout(-1);
    printw("Error: highscore.txt doesn\'t exists\n");
    getch();
  }

  endwin();
}

void gameLoop() {
  bool break_flag = true;

  int user_input;
  UserAction_t prev_action = noAction;
  GameState_t state = updateStateInfo();
  GameInfo_t status;
  bool hold = false;
  bool init_flag = true;

  while (break_flag) {
    if (state == Start) printStartMsg();

    UserAction_t action = getUserAction(prev_action, getch(), &hold);

    if (state == Start && (action == Start || action == Terminate))
      deleteStartMsg();
    if (state == GameOver) {
      if (action == Start) {
        initGame();
        deleteGameOverMsg();
        init_flag = true;
      }
      if (action == Terminate) break_flag = false;
    }

    userInput(action, hold);

    state = updateStateInfo();
    status = updateCurrentState();
    status.speed = status.level;

    if (state != Start && state != Pause && state != GameOver) render(status);

    if (state == GameOver && init_flag) {
      endGame();
      printGameOverMsg(status.score, status.high_score);
      init_flag = false;
    }

    prev_action = action;

    freeField(status.field);
    freeNext(status.next);
  }
}