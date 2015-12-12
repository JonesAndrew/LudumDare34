#include <SFML/Graphics.hpp>
#include "textureLoader.h"
#include <iostream>

class Actor : public sf::Drawable {
    sf::Vector2f pos;
    sf::Sprite sprite;
public:
    Actor();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
    void setPos(sf::Vector2f);
    sf::Vector2f getPos();
};
