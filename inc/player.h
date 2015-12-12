#include "actor.h"
#include "planet.h"
#include <memory>

#ifndef __Ludum_Dare__Player__
#define __Ludum_Dare__Player__

class Player : public Actor {
    int angle;
    std::shared_ptr<Planet> p;
public:
    Player();
    void setPlanet(std::shared_ptr<Planet>);
    virtual void update();
    void setAngle(int a);
    int getAngle();
};

#endif
