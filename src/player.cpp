#include "player.h"
#include <math.h>
#include "game.h"
#include "sound.h"

#define PI 3.14159265

#define DELAY 6

void Player::setPlanet(std::shared_ptr<Planet> plan) {
    p=plan;
}

std::shared_ptr<Planet> Player::getPlanet() {
    return p;
}

void Player::setAnimation(std::string s, bool loop) {
    if (canChange && deadCount == 0) {
        sprite.play(anim[s]);
        sprite.setLooped(loop);
    }
}

float distance2(sf::Vector2f a, sf::Vector2f b) {
    sf::Vector2f c=a-b;
    return sqrt(c.x*c.x+c.y*c.y);
}

void Player::update() {
    if (!laserSprite.getLooped() && laserSprite.isPlaying()) {
        for (int i=1;i<game->planets.size();i++) {
            if (distance2(laserSprite.getPosition(),game->planets[i]->getPos()) <= game->planets[i]->getRadius()+36) {
                if (game->planets[i]->getMass() < 35) {
                    game->planets[i]->deadCount = 2;
                } else {
                    game->planets[i]->setVelocity(sf::Vector2f(0,-45.0*sin(angle*PI/180)/game->planets[i]->getMass())+sf::Vector2f(-45.0*cos(angle*PI/180)/game->planets[i]->getMass(),0));
                }
            }
        }
    }

    if (deadCount == 60*60) {
        sprite.play(anim["dead"]);
        sprite.setLooped(false);
        deadCount--;
    }
    if (delay == oldDelay && freeze <= 0) {
        delay--;
        if(p == nullptr) {
            setAnimation("fly");
        } else {
            setAnimation("idle");
        }
    }
    if (delay < 0) {
        delay = 0;
    }
    oldDelay = delay;
    freeze--;
    if (freeze == 0) {
        if (p != nullptr) {
            if (p->getMass() < 35) {
                p->deadCount = 2;
            } else {
                p->setVelocity(sf::Vector2f(0,-45.0*sin(angle*PI/180)/p->getMass())+sf::Vector2f(-45.0*cos(angle*PI/180)/p->getMass(),0));
            }
            game->setShake(10);
            p = nullptr;
            velocity = sf::Vector2f(0,4.5*sin(angle*PI/180))+sf::Vector2f(4.5*cos(angle*PI/180),0);
            extra.setPosition(pos);
            extra.play(explosion);
            SoundPlayer::getInstance()->playSound("SmallJump.wav");
            canChange = true;
        } else {
            velocity.x = -velocity.x;
            velocity.y = -velocity.y;
            SoundPlayer::getInstance()->playSound("DoubleJump.wav");
            setAngle(getAngle()+180);
            laserSprite.play(laserShot);
            laserSprite.setLooped(false);
            laserSprite.setPosition(pos);
            laserSprite.setOrigin(0,36);
            //sprite.setRotation(angle+90);
        }
    }
    if (freeze > 0) {
        laserSprite.setPosition(pos);
    }
    if (freeze == -18) {
        canChange = true;
        sprite.setRotation(angle+90);
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
    laserSprite.update(sf::seconds(1.0/60.0));
}

Player::Player() {
    deadCount = 0;
    anim["idle"] = TextureLoader::getInstance()->getAnim("Jane.png");
    anim["idle"].addFrame(sf::IntRect(0, 0, 24, 24));
    anim["idle"].addFrame(sf::IntRect(24, 0, 24, 24));
    anim["idle"].addFrame(sf::IntRect(48, 0, 24, 24));
    anim["idle"].addFrame(sf::IntRect(72, 0, 24, 24));
    anim["walk"] = TextureLoader::getInstance()->getAnim("Jane.png");
    anim["walk"].addFrame(sf::IntRect(0+96, 0, 24, 24));
    anim["walk"].addFrame(sf::IntRect(24+96, 0, 24, 24));
    anim["walk"].addFrame(sf::IntRect(48+96, 0, 24, 24));
    anim["walk"].addFrame(sf::IntRect(72+96, 0, 24, 24));
    anim["crouch"] = TextureLoader::getInstance()->getAnim("Jane.png");
    anim["crouch"].addFrame(sf::IntRect(0, 24, 24, 24));
    anim["crouch"].addFrame(sf::IntRect(24, 24, 24, 24));
    anim["crouch"].addFrame(sf::IntRect(48, 24, 24, 24));
    anim["crouch"].addFrame(sf::IntRect(48, 24, 24, 24));
    anim["fly"] = TextureLoader::getInstance()->getAnim("Jane.png");
    anim["fly"].addFrame(sf::IntRect(48+96, 24, 24, 24));
    anim["fly"].addFrame(sf::IntRect(72+96, 24, 24, 24));
    anim["fly"].addFrame(sf::IntRect(0, 48, 24, 24));
    anim["fly"].addFrame(sf::IntRect(24, 48, 24, 24));
    anim["back"] = TextureLoader::getInstance()->getAnim("Jane.png");
    anim["back"].addFrame(sf::IntRect(48, 48, 24, 24));
    anim["back"].addFrame(sf::IntRect(72, 48, 24, 24));
    anim["back"].addFrame(sf::IntRect(96, 48, 24, 24));
    anim["back"].addFrame(sf::IntRect(96, 48, 24, 24));
    anim["back"].addFrame(sf::IntRect(96, 48, 24, 24));
    anim["dead"] = TextureLoader::getInstance()->getAnim("Jane.png");
    anim["dead"].addFrame(sf::IntRect(72, 72, 24, 24));
    anim["dead"].addFrame(sf::IntRect(96, 72, 24, 24));
    anim["dead"].addFrame(sf::IntRect(120, 72, 24, 24));
    anim["dead"].addFrame(sf::IntRect(144, 72, 24, 24));
    anim["dead"].addFrame(sf::IntRect(168, 72, 24, 24));
    anim["dead"].addFrame(sf::IntRect(0, 96, 24, 24));
    explosion = TextureLoader::getInstance()->getAnim("ExplosionSheet.png");
    explosion.addFrame(sf::IntRect(0, 24, 72, 48));
    explosion.addFrame(sf::IntRect(72, 24, 72, 48));
    explosion.addFrame(sf::IntRect(144, 24, 72, 48));
    explosion.addFrame(sf::IntRect(0, 72, 72, 48));
    explosion.addFrame(sf::IntRect(72, 72, 72, 48));
    laser = TextureLoader::getInstance()->getAnim("GunBlast.png");
    laser.addFrame(sf::IntRect(0,0,24,24));
    laser.addFrame(sf::IntRect(24,0,24,24));
    laser.addFrame(sf::IntRect(48,0,24,24));
    laser.addFrame(sf::IntRect(72,0,24,24));
    laserShot = TextureLoader::getInstance()->getAnim("GunBlast.png");
    laserShot.addFrame(sf::IntRect(0,24,72,72));
    laserShot.addFrame(sf::IntRect(72,24,72,72));
    laserShot.addFrame(sf::IntRect(144,24,72,72));
    laserShot.addFrame(sf::IntRect(216,24,72,72));
    laserShot.addFrame(sf::IntRect(216,24,0,0));

    extra.setOrigin(36,48);
    extra.setLooped(false);
    sprite.setOrigin(12,24);

    setAngle(90);

    delay = 0;
    oldDelay = 0;
    freeze = 0;
    canChange = true;

    setAnimation("idle",true);
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
    if (deadCount == 0) {
        if (p != nullptr && freeze <= 0) {
            freeze = 24;
            setAnimation("crouch",false);
            canChange = false;
        } else if (p == nullptr && dj) {
            dj = false;
            freeze = 12;
            setAnimation("back",false);
            canChange = false;
            if(sprite.getScale().x == -1) {
                sprite.setRotation(angle+180);
                laserSprite.setOrigin(-16,0);
                std::cout<<"-1 set\n";
            } else {
                sprite.setRotation(angle);
                laserSprite.setOrigin(-16,24);
                std::cout<<"+1 set\n";
            }
            laserSprite.setRotation(angle);
            laserSprite.play(laser);
            laserSprite.setLooped(true);
            laserSprite.setPosition(pos);
        }
    }
}

void Player::moveLeft() {
    if (deadCount == 0 && p != nullptr && freeze <= 0) {
        delay++;
        if (delay >= DELAY) {
            int r=p->getRadius();
            setAngle(getAngle()-(100.0/r));
        }
        setAnimation("walk");
        sprite.setScale(-1.f,1.f);
    } else if (deadCount == 0 && p == nullptr) {
        setAngle(getAngle()-0.5);
        velocity = sf::Vector2f(0,4.5*sin(angle*PI/180))+sf::Vector2f(4.5*cos(angle*PI/180),0);
    }
}

void Player::moveRight() {
    if (deadCount == 0 && p != nullptr && freeze <= 0) {
        delay++;
        if(delay >= DELAY) {
            int r=p->getRadius();
            setAngle(getAngle()+(100.0/r));
        }
        setAnimation("walk");
        sprite.setScale(1.f,1.f);
    } else if (deadCount == 0 && p == nullptr) {
        setAngle(getAngle()+0.5);
        velocity = sf::Vector2f(0,4.5*sin(angle*PI/180))+sf::Vector2f(4.5*cos(angle*PI/180),0);
    }
}

int Player::getFreeze() {
    return freeze;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates) const {
    target.draw(sprite);
    target.draw(extra);
    target.draw(laserSprite);
}

Player::~Player() {
    if (game) {
        game = nullptr;
    }
}
