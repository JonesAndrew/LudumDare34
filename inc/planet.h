#include "actor.h"

#ifndef __Ludum_Dare__Planet__
#define __Ludum_Dare__Planet__

class Planet : public Actor {
    int radius;
    int mass;
    std::vector<Animation> anim;
    std::string file;
public:
    bool home;
    Planet();
    ~Planet();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
    int getRadius();
    void setRadius(int);
    void setMass(int);
    int getMass();
    void setSprite(std::string,int);
    std::string getFile();
    virtual void setVelocity(sf::Vector2f);
    virtual void update();
};

#endif
