#include "planet.h"

Planet::Planet() {
    radius = 50;
    velocity = sf::Vector2f(0.2,0.37);
    mass = 60;
    dead = false;
}

void Planet::draw(sf::RenderTarget &target, sf::RenderStates) const {
    sf::CircleShape shape(radius);
    shape.setOrigin(radius,radius);
    shape.setPosition(pos);
    target.draw(shape);
    target.draw(sprite);
}

int Planet::getRadius() {
    return radius;
}

int Planet::getMass() {
    return mass;
}

void Planet::setMass(int m) {
    mass = m;
}

void Planet::setRadius(int r) {
    radius = r;
}

void Planet::setSprite(std::string file, int size) {
    anim = TextureLoader::getInstance()->getAnim(file);
    anim.addFrame(sf::IntRect(0, 0, size-1, size-1));
    sprite.setOrigin(size/2,size/2);
    sprite.play(anim);
}
