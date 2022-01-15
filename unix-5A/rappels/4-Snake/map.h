#ifndef __MAP_H__
#define __MAP_H__

#include "snake.h"

typedef enum {
    EMPTY      = ' ',
    WALL       = '#',
    SNAKE_HEAD = 'O',
    SNAKE_BODY = 'o',
    APPLE      = '@'
} cell;

typedef struct {
    unsigned int width, height;
    cell ** cells;
} map;

map newMap(unsigned int width, unsigned int height);
void deleteMap(map m);
void drawMap(map m, snake s);

void placeRandomApple(map m);
int getAppleLocation(map m, int *x, int *y);

int checkCollision(snake s, map m);

#endif