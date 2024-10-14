#ifndef BRICK_GAME_TETRIS_INC_OBJECTS_H
#define BRICK_GAME_TETRIS_INC_OBJECTS_H

typedef struct {
  int **blocks;
  int size;
  int next_size;
  int x;
  int y;
} Figure_t;

#define FIGURE_1     \
  {                  \
    {1, 1}, { 1, 1 } \
  }

#define FIGURE_2                      \
  {                                   \
    {1, 0, 0}, {1, 1, 1}, { 0, 0, 0 } \
  }

#define FIGURE_3                      \
  {                                   \
    {0, 0, 1}, {1, 1, 1}, { 0, 0, 0 } \
  }

#define FIGURE_4                      \
  {                                   \
    {0, 1, 1}, {1, 1, 0}, { 0, 0, 0 } \
  }

#define FIGURE_5                      \
  {                                   \
    {1, 1, 0}, {0, 1, 1}, { 0, 0, 0 } \
  }

#define FIGURE_6                      \
  {                                   \
    {0, 1, 0}, {1, 1, 1}, { 0, 0, 0 } \
  }

#define FIGURE_7                                             \
  {                                                          \
    {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, { 0, 0, 0, 0 } \
  }

#endif