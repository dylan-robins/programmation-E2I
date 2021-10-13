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
    unsigned int x, y;
    struct snakeBodyPart_s * next;
} snakeBodyPart;

// Représente un serpent: la tête et la direction dans laquelle il se déplace
typedef struct {
    direction heading;
    snakeBodyPart * head;
} snake;

snake newSnake(unsigned int x, unsigned int y);
void deleteSnake(snake s);
snakeBodyPart * newSnakeBodypart(unsigned int x, unsigned int y);
void moveSnake(snake * s);

int isSnakeHead(snake s, unsigned int x, unsigned int y);
int isSnakeBody(snake s, unsigned int x, unsigned int y);

int printSnake(snake s);

#endif