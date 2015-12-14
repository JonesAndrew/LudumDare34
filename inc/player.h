#include "actor.h"
#include "planet.h"
#include <memory>

#ifndef __Ludum_Dare__Player__
#define __Ludum_Dare__Player__

class Game;

class Player : public Actor {
    float angle;
    std::shared_ptr<Planet> p;
    int delay,oldDelay,freeze;
    Animation explosion,laser,laserShot;
    std::map<std::string, Animation> anim;
    AnimatedSprite extra;
    AnimatedSprite laserSprite;
    bool dj;
    bool canChange;
public:
    Player();
    ~Player();
    void setPlanet(std::shared_ptr<Planet>);
    std::shared_ptr<Planet> getPlanet();
    virtual void update();
    void setAngle(float a);
    float getAngle();
    void jump();
    void moveLeft();
    void moveRight();
    void setAnimation(std::string,bool loop=true);
    int getFreeze();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
};

#endif
