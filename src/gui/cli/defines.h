#ifndef GUI_CLI_DEFINES_H
#define GUI_CLI_DEFINES_H

#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 33

#define CONTROL_HEIGHT 9
#define CONTROL_WIDTH 16

#define STARTY 2
#define STARTX 2

#define CONTROL_STARTY STARTY
#define CONTROL_STARTX STARTX + SCREEN_WIDTH

#define BANNER_HEIGHT 2

#define BANNER_MSG "BRICK GAME"
#define BANNER_MSG_LEN 10
#define BANNER_MSG_STARTY 1
#define BANNER_MSG_STARTX (SCREEN_WIDTH - BANNER_MSG_LEN) / 2

#define FIELD_HEIGHT 22
#define FIELD_WIDTH 22
#define FIELD_STARTY STARTY + BANNER_HEIGHT
#define FIELD_STARTX STARTX + 1

#define BOARD_HEIGHT 21
#define BOARD_WIDTH 9
#define BOARD_STARTY FIELD_STARTY + 1
#define BOARD_STARTX FIELD_STARTX + FIELD_WIDTH

#define SCORE_MSG "SCORE"
#define SCORE_MSG_LEN 5
#define SCORE_MSG_STARTY 0
#define SCORE_MSG_STARTX BOARD_WIDTH - SCORE_MSG_LEN

#define HSCORE_MSG "HIGHSCORE"
#define HSCORE_MSG_LEN 9
#define HSCORE_MSG_STARTY 3
#define HSCORE_MSG_STARTX BOARD_WIDTH - HSCORE_MSG_LEN

#define NEXT_MSG "NEXT"
#define NEXT_MSG_LEN 4
#define NEXT_MSG_STARTY 6
#define NEXT_MSG_STARTX (BOARD_WIDTH - NEXT_MSG_LEN) / 2 + 1

#define LVL_MSG "LEVEL"
#define LVL_MSG_LEN 5
#define LVL_MSG_STARTY 12
#define LVL_MSG_STARTX BOARD_WIDTH - LVL_MSG_LEN

#define SPEED_MSG "SPEED"
#define SPEED_MSG_LEN 5
#define SPEED_MSG_STARTY 15
#define SPEED_MSG_STARTX BOARD_WIDTH - SPEED_MSG_LEN

#define PAUSE_MSG "PAUSE"
#define PAUSE_MSG_LEN 5
#define PAUSE_MSG_STARTY 19
#define PAUSE_MSG_STARTX (BOARD_WIDTH - PAUSE_MSG_LEN) / 2

#define START_MSG_1 "PRESS ENTER"
#define START_MSG_2 "TO START"
#define START_MSG_1_LEN 11
#define START_MSG_2_LEN 8
#define START_MSG_1_STARTY FIELD_HEIGHT / 2 - 1
#define START_MSG_1_STARTX (FIELD_WIDTH - START_MSG_1_LEN) / 2 + 1
#define START_MSG_2_STARTY FIELD_HEIGHT / 2
#define START_MSG_2_STARTX (FIELD_WIDTH - START_MSG_2_LEN) / 2 + 1

#define GAMEOVER_MSG "GAME OVER"
#define GAMEOVER_MSG_LEN 9
#define GAMEOVER_MSG_STARTY FIELD_HEIGHT / 2 - 2
#define GAMEOVER_MSG_STARTX (FIELD_WIDTH - GAMEOVER_MSG_LEN) / 2 + 1

#endif