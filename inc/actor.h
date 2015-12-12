#include <SFML/Graphics.hpp>
#include "textureLoader.h"
#include <iostream>

#ifndef __Ludum_Dare__Actor__
#define __Ludum_Dare__Actor__

class Actor : public sf::Drawable {
protected:
    sf::Vector2f pos;
    sf::Sprite sprite;
    sf::Vector2f velocity;
public:
    Actor();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
    void setPos(sf::Vector2f);
    sf::Vector2f getPos();
    virtual void update();
};

#endif
