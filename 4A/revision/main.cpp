#include <array>
#include <cstring>
#include <iostream>

class Entity {
  private:
    float _x, _y;
    char *_name;

  public:
    Entity() : _x(0), _y(0) {
        _name = new char[10];
        strcpy(_name, "Default");
    }
    Entity(float x, float y, const char *name) : _x(x), _y(y) {
        _name = new char[strlen(name)];
        strcpy(_name, name);
    }
    Entity(Entity &other) : _x(other._x), _y(other._y) {
        _name = new char[strlen(other._name)];
        strcpy(_name, other._name);
    }

    const char *get_name() const {
        return _name;
    }

    float get_x() const {
        return _x;
    }
    float get_y() const {
        return _y;
    }

    virtual void display() = 0;
};

class Player : public Entity {
  private:
    int _score;
    //float _texture[1000][1000][3];

  public:
    Player() : Entity(), _score(0) {}
    Player(float x, float y, const char *name, int score, const char *texture_path)
        : Entity(x, y, name), _score(score) {}

    void display() {
        std::cout << "Player ["
                  << get_name() << ", "
                  << "(" << get_x() << "," << get_y() << ")"
                  << ", "
                  << _score
                  << "]" << std::endl;
    }
};

class Enemy : public Entity {
  private:
    //float _texture[1000][1000][3];
    int _hp;

  public:
    Enemy() : Entity(), _hp(0) {}
    Enemy(float x, float y, const char *name, int hp, const char *texture_path)
        : Entity(x, y, name), _hp(hp) {}

    void display() {
        std::cout << "Enemy ["
                  << get_name() << ", "
                  << "(" << get_x() << "," << get_y() << ")"
                  << ", "
                  << _hp
                  << "]" << std::endl;
    }
};

void render_entity(Entity *e) {
    // des trucs
    e->display();
}

main() {
    std::array<Entity *, 10> table;

    for (int i = 0; i < 3; i++) {
        table[i] = new Player(0, 0, "Player", 0, "./player1.png");
    }
    for (int i = 3; i < 10; i++) {
        table[i] = new Enemy(0, 0, "Player", 100, "./enemy.png");
    }

    for (int i = 0; i < 10; i++) {
        render_entity(table[i]);
    }

    return 0;
}