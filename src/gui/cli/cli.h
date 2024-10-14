#ifndef GUI_CLI_CLI_H
#define GUI_CLI_CLI_H

#include <ncurses.h>
#include <time.h>

#include "../../brick_game/brick_game.h"
#include "defines.h"

void initCli();

void winSizeControl();

void printInitScreen(int highscore, char *action_msg);

void render(GameInfo_t status);

void printControl(char *action_msg);

void printStartMsg();

void deleteStartMsg();

void updateField(int **field_blocks);

void updateBoard(GameInfo_t status);

void printGameOverMsg(int score, int high_score);

void deleteGameOverMsg();

#endif