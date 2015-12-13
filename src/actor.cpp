#include "actor.h"

Actor::Actor() {
    std::cout<<"test\n";
}

void Actor::draw(sf::RenderTarget &target, sf::RenderStates) const {
    target.draw(sprite);
}

void Actor::setPos(sf::Vector2f p) {
    pos=p;
    sprite.setPosition(p);
}

sf::Vector2f Actor::getPos() {
    return pos;
}

void Actor::update() {
    setPos(pos+velocity);
}

void Actor::setVelocity(sf::Vector2f a) {
    velocity = a;
}

sf::Vector2f Actor::getVelocity() {
    return velocity;
}
