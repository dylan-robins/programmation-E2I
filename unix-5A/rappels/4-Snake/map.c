#include "map.h"
#include "snake.h"
#include "ttyGraphics.h"

#include <stdio.h>
#include <stdlib.h>

map newMap(unsigned int width, unsigned int height) {
    map m;
    m.width = width;
    m.height = height - 1; // - 1 pour barre d'info/de status en bas!

    // Allouer la map
    m.cells = (cell **)malloc(m.height * sizeof(cell *));
    for (unsigned int i = 0; i < m.height; i++) {
        m.cells[i] = (cell *)malloc(m.width * sizeof(cell));
    }

    // Initialiser chaque case
    for (unsigned int i = 0; i < m.height; i++) {
        for (unsigned int j = 0; j < m.width; j++) {
            if (i == 0 || j == 0 || i == m.height - 1 || j == m.width - 1) {
                m.cells[i][j] = WALL;
            } else {
                m.cells[i][j] = EMPTY;
            }
        }
    }

    placeRandomApple(m);

    return m;
}

void deleteMap(map m) {
    for (unsigned int i = 0; i < m.height; i++) {
        free(m.cells[i]);
    }
    free(m.cells);
}

void drawMap(map m, snake s) {
    clear();

    for (unsigned int i = 0; i < m.height; i++) {
        for (unsigned int j = 0; j < m.width; j++) {
            if (isSnakeHead(s, j, i)) {
                putc(SNAKE_HEAD, stdout);
            } else if (isSnakeBody(s, j, i)) {
                putc(SNAKE_BODY, stdout);
            } else {
                putc(m.cells[i][j], stdout);
            }
        }
        putc('\n', stdout);
    }
}

void placeRandomApple(map m) {
    int x = rand() % m.width;
    int y = rand() % m.height;
    m.cells[y][x] = APPLE;
}

int getAppleLocation(map m, int *x, int *y) {
    for (unsigned int i = 0; i < m.height; i++) {
        for (unsigned int j = 0; j < m.width; j++) {
            if (m.cells[i][j] == APPLE) {
                *x = j;
                *y = i;
                return 1;
            }
        }
    }
    return 0;
}

int checkCollision(snake s, map m) {
    int apple_x, apple_y;
    getAppleLocation(m, &apple_x, &apple_y);

    // Check out of bounds
    if ((s.head->x <= 0 || s.head->x >= m.width) || (s.head->y <= 0 || s.head->y >= m.height))
        return -1;

    // Check self eating
    if (isSnakeBody(s, s.head->x, s.head->y)) {
        printf("CHOMP\n");
        return -1;
    }

    // Check apple
    if (isSnakeHead(s, apple_x, apple_y) || isSnakeBody(s, apple_x, apple_y)) {
        printf("NOMNOMNOM\n");
        m.cells[apple_y][apple_x] = EMPTY;
        placeRandomApple(m);
        return 1;
    }

    return 0;
}