#include "actor.h"
#include <memory>

#ifndef __Ludum_Dare__Player__
#define __Ludum_Dare__Player__

class Game;

class Player : public Actor {
    sf::RectangleShape sprite;
public:
    Player();
    ~Player();
    virtual void update();
    void jump();
    void moveLeft();
    void moveRight();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
    bool dj;
    bool grounded;
};

#endif
