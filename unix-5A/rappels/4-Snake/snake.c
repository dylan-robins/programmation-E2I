#include "snake.h"

#include <stdio.h>
#include <stdlib.h>

snake newSnake(unsigned int x, unsigned int y) {
    snake s;
    s.heading = EAST;
    s.head = newSnakeBodypart(x, y);
    s.head->next = newSnakeBodypart(x - 1, y);
    s.head->next->next = newSnakeBodypart(x - 2, y);
    return s;
}

void deleteSnake(snake s) {
    snakeBodyPart *current = s.head;
    snakeBodyPart *to_del = NULL;
    while (current != NULL) {
        to_del = current;
        current = current->next;
        free(to_del);
    }
}

snakeBodyPart *newSnakeBodypart(unsigned int x, unsigned int y) {
    snakeBodyPart *bodyPart = (snakeBodyPart *)malloc(sizeof(snakeBodyPart));
    bodyPart->x = x;
    bodyPart->y = y;
    bodyPart->next = NULL;
    return bodyPart;
}

void getNewHeadPosition(int x, int y, direction d, int *new_x, int *new_y) {
    switch (d) {
        case NORTH:
            *new_x = x;
            *new_y = y - 1;
            break;
        case EAST:
            *new_x = x + 1;
            *new_y = y;
            break;
        case SOUTH:
            *new_x = x;
            *new_y = y + 1;
            break;
        case WEST:
            *new_x = x - 1;
            *new_y = y;
            break;
        case NONE:
            *new_x = x;
            *new_y = y;
            break;
    }
}

void lengthenSnake(snake *s, direction d) {
    int new_x, new_y;
    snakeBodyPart * oldHead = s->head;

    getNewHeadPosition(oldHead->x, oldHead->y, d, &new_x, &new_y);
    snakeBodyPart *newHead = newSnakeBodypart(new_x, new_y);
    newHead->next = oldHead;
    s->head = newHead;
}

void moveSnake(snake *s) {
    lengthenSnake(s, s->heading);
}

int isSnakeHead(snake s, unsigned int x, unsigned int y) {
    return s.head != NULL && s.head->x == x && s.head->y == y;
}

int isSnakeBody(snake s, unsigned int x, unsigned int y) {
    if (isSnakeHead(s, x, y))
        return 0;

    for (snakeBodyPart *cur = s.head->next; cur != NULL; cur = cur->next)
        if (cur->x == x && cur->y == y) return 1;

    return 0;
}


int printSnake(snake s) {
    for (snakeBodyPart *cur = s.head; cur != NULL; cur = cur->next)
        printf("(%d,%d)->", cur->x, cur->y);
    printf("NULL");

    return 0;
}