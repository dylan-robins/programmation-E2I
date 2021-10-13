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
    m.cells = (cell **) malloc(m.height * sizeof(cell *));
    for (unsigned int i = 0; i < m.height; i++) {
        m.cells[i] = (cell *) malloc(m.width * sizeof(cell));
    }

    // Initialiser chaque case
    for (unsigned int i = 0; i < m.height; i++) {
        for (unsigned int j = 0; j < m.width; j++) {
            if (i == 0 || j == 0 || i == m.height-1 || j == m.width-1) {
                m.cells[i][j] = WALL;
            } else {
                m.cells[i][j] = EMPTY;
            }
        }
    }

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