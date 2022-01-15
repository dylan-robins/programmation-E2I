#ifndef __SNAKE_H__
#define __SNAKE_H__

typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    NONE
} direction;

// Noeud d'une liste chaînée
typedef struct snakeBodyPart_s {
    int x, y;
    struct snakeBodyPart_s * prev;
    struct snakeBodyPart_s * next;
} snakeBodyPart;

// Représente un serpent: la tête et la direction dans laquelle il se déplace
typedef struct {
    direction heading;
    snakeBodyPart * head;
    snakeBodyPart * tail;
} snake;

snake newSnake(int x, int y);
void deleteSnake(snake s);
snakeBodyPart * newSnakeBodypart(int x, int y);
void moveSnake(snake * s);
void lengthenSnake(snake *s);

int isSnakeHead(snake s, int x, int y);
int isSnakeBody(snake s, int x, int y);

int printSnake(snake s);

#endif