#include "actor.h"
#include "game.h"

Actor::Actor() {
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
    if (deadCount > 0) {
        deadCount--;
    } else {
        setPos(pos+velocity);
    }
}

void Actor::setVelocity(sf::Vector2f a) {
    velocity = a;
}

sf::Vector2f Actor::getVelocity() {
    return velocity;
}

void Actor::setGame(Game* g) {
    game = g;
}
