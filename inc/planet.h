#include "actor.h"

#ifndef __Ludum_Dare__Planet__
#define __Ludum_Dare__Planet__

class Planet : public Actor {
    int radius;
    int mass;
public:
    Planet();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
    int getRadius();
};

#endif
