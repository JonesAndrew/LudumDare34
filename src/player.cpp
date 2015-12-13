#include "player.h"
#include <math.h>

#define PI 3.14159265

#define DELAY 5

void Player::setPlanet(std::shared_ptr<Planet> plan) {
    p=plan;
}

std::shared_ptr<Planet> Player::getPlanet() {
    return p;
}

void Player::update() {
    if (delay == oldDelay) {
        delay--;
        sprite.play(walk);
    }
    if (delay < 0) {
        delay = 0;
    }
    oldDelay = delay;
    if (p == nullptr) {
        Actor::update();
    } else {
        setPos(p->getPos()+sf::Vector2f(0,p->getRadius()*sin(angle*PI/180))+
        sf::Vector2f(p->getRadius()*cos(angle*PI/180),0));
    }
    sprite.update(sf::seconds(1.0/60.0));
}

Player::Player() {
    anim = TextureLoader::getInstance()->getAnim("Jane.png");
    anim.addFrame(sf::IntRect(0, 0, 24, 24));
    anim.addFrame(sf::IntRect(24, 0, 24, 24));
    anim.addFrame(sf::IntRect(48, 0, 24, 24));
    anim.addFrame(sf::IntRect(72, 0, 24, 24));
    walk = TextureLoader::getInstance()->getAnim("Jane.png");
    walk.addFrame(sf::IntRect(0+96, 0, 24, 24));
    walk.addFrame(sf::IntRect(24+96, 0, 24, 24));
    walk.addFrame(sf::IntRect(48+96, 0, 24, 24));
    walk.addFrame(sf::IntRect(72+96, 0, 24, 24));
    sprite.setOrigin(12,24);
    setAngle(90);
    delay = 0;
    oldDelay = 0;
    sprite.play(anim);
}

void Player::setAngle(float a) {
    angle = a;
    sprite.setRotation(angle+90);
}

float Player::getAngle() {
    return angle;
}

void Player::jump() {
    p = nullptr;
    velocity = sf::Vector2f(0,4.5*sin(angle*PI/180))+sf::Vector2f(4.5*cos(angle*PI/180),0);
}

void Player::moveLeft() {
    delay++;
    if (p != nullptr) {
        if (delay >= DELAY) {
            int r=p->getRadius();
            setAngle(getAngle()-r/30.0);
        }
        sprite.play(walk);
        sprite.setScale(-1.f,1.f);
    }
}

void Player::moveRight() {
    delay++;
    if (p != nullptr) {
        if(delay >= DELAY) {
            int r=p->getRadius();
            setAngle(getAngle()+r/30.0);
        }
        sprite.play(walk);
        sprite.setScale(1.f,1.f);
    }
}
