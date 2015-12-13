#include "planet.h"

Planet::Planet() {
    radius = 50;
    velocity = sf::Vector2f(0.2,0.37);
    mass = 60;
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
