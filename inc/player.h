#include "actor.h"
#include "planet.h"
#include <memory>

#ifndef __Ludum_Dare__Player__
#define __Ludum_Dare__Player__

class Player : public Actor {
    float angle;
    std::shared_ptr<Planet> p;
    int delay,oldDelay;
    Animation anim,walk;
public:
    Player();
    void setPlanet(std::shared_ptr<Planet>);
    std::shared_ptr<Planet> getPlanet();
    virtual void update();
    void setAngle(float a);
    float getAngle();
    void jump();
    void moveLeft();
    void moveRight();
};

#endif
