#include "snake.h"

#include <stdio.h>
#include <stdlib.h>

snake newSnake(int x, int y) {
    snake s;
    s.heading = EAST;
    s.head = newSnakeBodypart(x, y);
    snakeBodyPart * mid = newSnakeBodypart(x - 1, y);
    s.tail = newSnakeBodypart(x - 2, y);
    
    s.head->next = mid;
    mid->prev = s.head;
    mid->next = s.tail;
    s.tail->prev = mid;

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

snakeBodyPart *newSnakeBodypart(int x, int y) {
    snakeBodyPart *bodyPart = (snakeBodyPart *)malloc(sizeof(snakeBodyPart));
    bodyPart->x = x;
    bodyPart->y = y;
    bodyPart->prev = NULL;
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

void lengthenSnake(snake *s) {
    int new_x, new_y;
    getNewHeadPosition(s->head->x, s->head->y, s->heading, &new_x, &new_y);

    snakeBodyPart * oldHead = s->head;
    snakeBodyPart * newHead = newSnakeBodypart(new_x, new_y);
    newHead->next = oldHead;
    s->head = newHead;

    oldHead->next->prev = newHead;
}

void moveSnake(snake *s) {
    // détacher la queue du serpent
    snakeBodyPart * newHead = s->tail;
    s->tail = newHead->prev;
    s->tail->next = NULL;
    newHead->prev = NULL;

    // Déplacer le maillon
    getNewHeadPosition(s->head->x, s->head->y, s->heading, &(newHead->x), &(newHead->y));

    // Le réattacher en tête
    newHead->next = s->head;
    s->head->prev = newHead;
    s->head = newHead;
}

int isSnakeHead(snake s, int x, int y) {
    return s.head != NULL && s.head->x == x && s.head->y == y;
}

int isSnakeBody(snake s, int x, int y) {
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
