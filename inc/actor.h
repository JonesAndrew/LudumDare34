#include <SFML/Graphics.hpp>
#include "textureLoader.h"
#include <iostream>
#include "AnimatedSprite.hpp"

#ifndef __Ludum_Dare__Actor__
#define __Ludum_Dare__Actor__

class Game;

class Actor : public sf::Drawable {
protected:
    sf::Vector2f pos;
    //AnimatedSprite sprite;
    sf::Vector2f velocity;
    Game *game;
public:
    int deadCount;
    Actor();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
    void setPos(sf::Vector2f);
    sf::Vector2f getPos();
    virtual void update();
    virtual void setVelocity(sf::Vector2f);
    sf::Vector2f getVelocity();
    void setGame(Game*);
};

#endif
