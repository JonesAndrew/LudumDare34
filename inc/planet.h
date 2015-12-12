#include "actor.h"

#ifndef __Ludum_Dare__Planet__
#define __Ludum_Dare__Planet__

class Planet : public Actor {
    int radius;
public:
    Planet();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates) const;
};

#endif
