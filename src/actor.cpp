#include "actor.h"

Actor::Actor() {
    std::cout<<"test\n";
    sprite = TextureLoader::getInstance()->getSprite("test.png");
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
