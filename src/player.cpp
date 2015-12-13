#include "player.h"
#include <math.h>
#include "game.h"

#define PI 3.14159265

#define DELAY 6

void Player::setPlanet(std::shared_ptr<Planet> plan) {
    p=plan;
}

std::shared_ptr<Planet> Player::getPlanet() {
    return p;
}

void Player::update() {
    if (delay == oldDelay && freeze <= 0) {
        delay--;
        if(p == nullptr) {
            sprite.play(fly);
        } else {
            sprite.play(anim);
        }
        sprite.setLooped(true);
    }
    if (delay < 0) {
        delay = 0;
    }
    oldDelay = delay;
    freeze--;
    if (freeze == 0) {
        if (p->getMass() < 35) {
            p->dead = true;
        } else {
            p->setVelocity(sf::Vector2f(0,-45.0*sin(angle*PI/180)/p->getMass())+sf::Vector2f(-45.0*cos(angle*PI/180)/p->getMass(),0));
        }
        game->setShake(10);
        p = nullptr;
        velocity = sf::Vector2f(0,4.5*sin(angle*PI/180))+sf::Vector2f(4.5*cos(angle*PI/180),0);
        extra.setPosition(pos);
        extra.play(explosion);
    }
    if (p == nullptr) {
        Actor::update();
    } else {
        setPos(p->getPos()+sf::Vector2f(0,p->getRadius()*sin(angle*PI/180))+
        sf::Vector2f(p->getRadius()*cos(angle*PI/180),0));
        dj = true;
    }
    sprite.update(sf::seconds(1.0/60.0));
    extra.update(sf::seconds(1.0/60.0));
}

Player::Player() {
    dead = false;
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
    crouch = TextureLoader::getInstance()->getAnim("Jane.png");
    crouch.addFrame(sf::IntRect(0, 24, 24, 24));
    crouch.addFrame(sf::IntRect(24, 24, 24, 24));
    crouch.addFrame(sf::IntRect(48, 24, 24, 24));
    crouch.addFrame(sf::IntRect(48, 24, 24, 24));
    fly = TextureLoader::getInstance()->getAnim("Jane.png");
    fly.addFrame(sf::IntRect(48+96, 24, 24, 24));
    fly.addFrame(sf::IntRect(72+96, 24, 24, 24));
    fly.addFrame(sf::IntRect(0, 48, 24, 24));
    fly.addFrame(sf::IntRect(24, 48, 24, 24));
    explosion = TextureLoader::getInstance()->getAnim("ExplosionSheet.png");
    explosion.addFrame(sf::IntRect(0, 0, 72, 72));
    explosion.addFrame(sf::IntRect(72, 0, 72, 72));
    explosion.addFrame(sf::IntRect(144, 0, 72, 72));
    explosion.addFrame(sf::IntRect(216, 0, 72, 72));
    extra.setOrigin(36,72);
    extra.setLooped(false);
    sprite.setOrigin(12,24);
    setAngle(90);
    delay = 0;
    oldDelay = 0;
    freeze = 0;
    sprite.play(anim);
}

void Player::setAngle(float a) {
    angle = a;
    sprite.setRotation(angle+90);
    extra.setRotation(angle+90);
}

float Player::getAngle() {
    return angle;
}

void Player::jump() {
    if (p != nullptr && freeze <= 0) {
        sprite.play(crouch);
        freeze = 24;
    } else if (p == nullptr && dj) {
        velocity.x = -velocity.x;
        velocity.y = -velocity.y;
        dj = false;
    }
}

void Player::moveLeft() {
    delay++;
    if (p != nullptr && freeze <= 0) {
        if (delay >= DELAY) {
            int r=p->getRadius();
            setAngle(getAngle()-(100.0/r));
        }
        sprite.play(walk);
        sprite.setLooped(true);
        sprite.setScale(-1.f,1.f);
    }
}

void Player::moveRight() {
    delay++;
    if (p != nullptr && freeze <= 0) {
        if(delay >= DELAY) {
            int r=p->getRadius();
            setAngle(getAngle()+(100.0/r));
        }
        sprite.play(walk);
        sprite.setLooped(true);
        sprite.setScale(1.f,1.f);
    }
}

void Player::setGame(Game* g) {
    game = g;
}

int Player::getFreeze() {
    return freeze;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates) const {
    target.draw(sprite);
    target.draw(extra);
}
