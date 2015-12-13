#include "actor.h"

#ifndef __Ludum_Dare__Planet__
#define __Ludum_Dare__Planet__

class Planet : public Actor {
    int radius;
    int mass;
    Animation anim;
    bool home;
public:
    Planet();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
    int getRadius();
    void setRadius(int);
    void setMass(int);
    int getMass();
    void setSprite(std::string,int);
    virtual void setVelocity(sf::Vector2f);
    virtual void update();
};

#endif
