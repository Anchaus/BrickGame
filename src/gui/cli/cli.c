#include "cli.h"

void initCli() {
  initscr();
  cbreak();
  noecho();
  timeout(10);
  keypad(stdscr, TRUE);
  curs_set(0);
}

void winSizeControl() {
  while (LINES < SCREEN_HEIGHT + 2 || COLS < SCREEN_WIDTH + CONTROL_WIDTH + 2) {
    clear();
    mvprintw((LINES - 3) / 2, (COLS - 18) / 2, "Window is to small");
    mvprintw((LINES - 3) / 2 + 1, (COLS - 18) / 2, "Need: %dx%d", SCREEN_HEIGHT,
             SCREEN_WIDTH + CONTROL_WIDTH);
    mvprintw((LINES - 3) / 2 + 2, (COLS - 18) / 2, "Is:   %dx%d", LINES, COLS);
    refresh();
    getch();
  }
  clear();
  refresh();
}

void printInitScreen(int highscore, char *action_msg) {
  winSizeControl();

  WINDOW *screen = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, STARTY, STARTX);
  WINDOW *field = newwin(FIELD_HEIGHT, FIELD_WIDTH, FIELD_STARTY, FIELD_STARTX);
  WINDOW *board = newwin(BOARD_HEIGHT, BOARD_WIDTH, BOARD_STARTY, BOARD_STARTX);

  box(screen, 0, 0);
  mvwprintw(screen, BANNER_MSG_STARTY, BANNER_MSG_STARTX, BANNER_MSG);
  wrefresh(screen);

  box(field, 0, 0);
  wrefresh(field);

  mvwprintw(board, SCORE_MSG_STARTY, SCORE_MSG_STARTX, SCORE_MSG);
  mvwprintw(board, SCORE_MSG_STARTY + 1, SCORE_MSG_STARTX, "%05d", 0);
  mvwprintw(board, HSCORE_MSG_STARTY, HSCORE_MSG_STARTX, HSCORE_MSG);
  mvwprintw(board, NEXT_MSG_STARTY, NEXT_MSG_STARTX, NEXT_MSG);
  mvwprintw(board, LVL_MSG_STARTY, LVL_MSG_STARTX, LVL_MSG);
  mvwprintw(board, LVL_MSG_STARTY + 1, BOARD_WIDTH - 2, "%02d", 0);
  mvwprintw(board, SPEED_MSG_STARTY, SPEED_MSG_STARTX, SPEED_MSG);
  mvwprintw(board, SPEED_MSG_STARTY + 1, BOARD_WIDTH - 2, "%02d", 0);
  wrefresh(board);

  printControl(action_msg);

  delwin(screen);
  delwin(field);
  delwin(board);
}

void render(GameInfo_t status) {
  if (status.field != NULL) updateField(status.field);
  if (status.next != NULL) updateBoard(status);
}

void printControl(char *action_msg) {
  WINDOW *control =
      newwin(CONTROL_HEIGHT, CONTROL_WIDTH, CONTROL_STARTY, CONTROL_STARTX);

  box(control, 0, 0);
  mvwprintw(control, 1, (CONTROL_WIDTH - 8) / 2, "CONTROL");
  mvwprintw(control, 3, 1, "ENTER - START");
  mvwprintw(control, 4, 1, "P - PAUSE");
  mvwprintw(control, 5, 1, "ESC - EXIT");
  wmove(control, 6, 1);
  waddch(control, ACS_LARROW);
  waddch(control, ACS_UARROW);
  waddch(control, ACS_DARROW);
  waddch(control, ACS_RARROW);
  wprintw(control, " - MOVE");
  mvwprintw(control, 7, 1, "SPACE - %s", action_msg);
  wrefresh(control);

  delwin(control);
}

void printStartMsg() {
  WINDOW *field = newwin(FIELD_HEIGHT, FIELD_WIDTH, FIELD_STARTY, FIELD_STARTX);

  box(field, 0, 0);
  mvwprintw(field, START_MSG_1_STARTY, START_MSG_1_STARTX, START_MSG_1);
  mvwprintw(field, START_MSG_2_STARTY, START_MSG_2_STARTX, START_MSG_2);
  wrefresh(field);

  delwin(field);
}

void deleteStartMsg() {
  WINDOW *field = newwin(FIELD_HEIGHT, FIELD_WIDTH, FIELD_STARTY, FIELD_STARTX);

  box(field, 0, 0);
  wmove(field, START_MSG_1_STARTY, START_MSG_1_STARTX);
  for (int i = 0; i < START_MSG_1_LEN; i++) waddch(field, ' ');
  wmove(field, START_MSG_2_STARTY, START_MSG_2_STARTX);
  for (int i = 0; i < START_MSG_2_LEN; i++) waddch(field, ' ');

  wrefresh(field);
  delwin(field);
}

void updateField(int **field_blocks) {
  WINDOW *field = newwin(FIELD_HEIGHT, FIELD_WIDTH, FIELD_STARTY, FIELD_STARTX);

  box(field, 0, 0);
  for (int i = 0; i < FIELD_HEIGHT - 2; i++) {
    for (int j = 0; j < (FIELD_WIDTH - 2) / 2; j++) {
      wmove(field, i + 1, j * 2 + 1);
      if (field_blocks[i][j]) {
        wattron(field, A_REVERSE);
        wprintw(field, "  ");
        wattroff(field, A_REVERSE);
      } else
        wprintw(field, "  ");
    }
  }
  wrefresh(field);

  delwin(field);
}

void updateBoard(GameInfo_t status) {
  WINDOW *board = newwin(BOARD_HEIGHT, BOARD_WIDTH, BOARD_STARTY, BOARD_STARTX);

  mvwprintw(board, SCORE_MSG_STARTY, SCORE_MSG_STARTX, SCORE_MSG);
  mvwprintw(board, HSCORE_MSG_STARTY, HSCORE_MSG_STARTX, HSCORE_MSG);
  mvwprintw(board, NEXT_MSG_STARTY, NEXT_MSG_STARTX, NEXT_MSG);
  mvwprintw(board, LVL_MSG_STARTY, LVL_MSG_STARTX, LVL_MSG);
  mvwprintw(board, SPEED_MSG_STARTY, SPEED_MSG_STARTX, SPEED_MSG);

  mvwprintw(board, SCORE_MSG_STARTY + 1, SCORE_MSG_STARTX, "%05d",
            status.score);
  mvwprintw(board, HSCORE_MSG_STARTY + 1, BOARD_WIDTH - 5, "%05d",
            status.high_score);
  mvwprintw(board, LVL_MSG_STARTY + 1, BOARD_WIDTH - 2, "%02d", status.level);
  mvwprintw(board, SPEED_MSG_STARTY + 1, BOARD_WIDTH - 2, "%02d", status.speed);

  static bool pause_flag = false;
  if (status.pause) {
    wattron(board, A_BLINK);
    mvwprintw(board, PAUSE_MSG_STARTY, PAUSE_MSG_STARTX, PAUSE_MSG);
    wattroff(board, A_BLINK);
    pause_flag = true;
  } else if (pause_flag) {
    wmove(board, PAUSE_MSG_STARTY, PAUSE_MSG_STARTX);
    for (int i = 0; i < PAUSE_MSG_LEN; i++) waddch(board, ' ');
  }

  if (status.next != NULL) {
    for (int i = 1; i <= 4; i++) {
      for (int j = 0; j < 4; j++) {
        wmove(board, NEXT_MSG_STARTY + i, NEXT_MSG_STARTX - 2 + j * 2);
        if (status.next[i - 1][j]) {
          wattron(board, A_REVERSE);
          wprintw(board, "  ");
          wattroff(board, A_REVERSE);
        } else
          wprintw(board, "  ");
      }
    }
  }

  wrefresh(board);
  delwin(board);
}

void printGameOverMsg(int score, int high_score) {
  WINDOW *field = newwin(FIELD_HEIGHT, FIELD_WIDTH, FIELD_STARTY, FIELD_STARTX);

  box(field, 0, 0);
  mvwprintw(field, GAMEOVER_MSG_STARTY, GAMEOVER_MSG_STARTX, GAMEOVER_MSG);
  mvwprintw(field, GAMEOVER_MSG_STARTY + 2, GAMEOVER_MSG_STARTX - 3,
            "SCORE: %d", score);
  if (high_score > score || high_score == 0)
    mvwprintw(field, GAMEOVER_MSG_STARTY + 3, GAMEOVER_MSG_STARTX - 3,
              "HIGHSCORE: %d", high_score);
  else
    mvwprintw(field, GAMEOVER_MSG_STARTY + 3, (FIELD_WIDTH - 14) / 2,
              "NEW HIGHSCORE!");

  mvwprintw(field, FIELD_HEIGHT - 3, (FIELD_WIDTH - 20) / 2,
            "PRESS ENTER TO START");
  mvwprintw(field, FIELD_HEIGHT - 2, (FIELD_WIDTH - 17) / 2,
            "PRESS ESC TO EXIT");
  wrefresh(field);

  delwin(field);
}

void deleteGameOverMsg() {
  WINDOW *field = newwin(FIELD_HEIGHT, FIELD_WIDTH, FIELD_STARTY, FIELD_STARTX);

  box(field, 0, 0);
  for (int i = GAMEOVER_MSG_STARTY; i <= GAMEOVER_MSG_STARTY + 3; i++) {
    wmove(field, i, 1);
    for (int j = 1; j < FIELD_WIDTH - 1; j++) waddch(field, ' ');
  }

  for (int i = FIELD_HEIGHT - 3; i < FIELD_HEIGHT - 1; i++) {
    wmove(field, i, 1);
    for (int j = 1; j < FIELD_WIDTH - 1; j++) waddch(field, ' ');
  }

  delwin(field);
}