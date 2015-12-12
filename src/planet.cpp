#include "planet.h"

Planet::Planet() {
    sprite = TextureLoader::getInstance()->getSprite("test.png");
    radius = 10;
    velocity = sf::Vector2f(0.4,0.67);
}

void Planet::draw(sf::RenderTarget &target, sf::RenderStates) const {
    //target.draw(sprite);
    sf::CircleShape shape(radius);
    shape.setOrigin(radius,radius);
    shape.setPosition(pos);
    target.draw(shape);
}

int Planet::getRadius() {
    return radius;
}
