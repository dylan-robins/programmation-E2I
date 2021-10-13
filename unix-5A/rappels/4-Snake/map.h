#ifndef __MAP_H__
#define __MAP_H__

#include "snake.h"

typedef enum {
    EMPTY      = ' ',
    WALL       = '#',
    SNAKE_HEAD = 'O',
    SNAKE_BODY = 'o'
} cell;

typedef struct {
    unsigned int width, height;
    cell ** cells;
} map;

map newMap(unsigned int width, unsigned int height);
void deleteMap(map m);
void drawMap(map m, snake s);

#endif