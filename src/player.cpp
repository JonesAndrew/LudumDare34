#include "player.h"
#include <math.h>

#define PI 3.14159265

void Player::setPlanet(std::shared_ptr<Planet> plan) {
    p=plan;
}

void Player::update() {
    if (p == nullptr) {
        Actor::update();
    } else {
        setPos(p->getPos()+sf::Vector2f(0,p->getRadius()*sin(angle*PI/180))+
        sf::Vector2f(p->getRadius()*cos(angle*PI/180),0));
    }
}

Player::Player() {
    sprite = TextureLoader::getInstance()->getSprite("test.png");
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    angle = 90;
}

void Player::setAngle(int a) {
    angle = a;
}

int Player::getAngle() {
    return angle;
}
