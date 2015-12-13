#include <SFML/Graphics.hpp>
#include "textureLoader.h"
#include <iostream>
#include "AnimatedSprite.hpp"

#ifndef __Ludum_Dare__Actor__
#define __Ludum_Dare__Actor__

class Actor : public sf::Drawable {
protected:
    sf::Vector2f pos;
    AnimatedSprite sprite;
    sf::Vector2f velocity;
public:
    bool dead;
    Actor();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
    void setPos(sf::Vector2f);
    sf::Vector2f getPos();
    virtual void update();
    virtual void setVelocity(sf::Vector2f);
    sf::Vector2f getVelocity();
};

#endif
