//
//  Director.h
//  Ludum Dare
//
//  Created by Andrew Jones on 8/22/14.
//  Copyright (c) 2014 Andrew Jones. All rights reserved.
//

#ifndef __Ludum_Dare__Director__
#define __Ludum_Dare__Director__

#include <iostream>
#include "scene.h"
#include <SFML/Network.hpp>

class Director {

    sf::RenderWindow window;

    sf::Clock timer;

    sf::Time time_now;
    sf::Time time_old;
    sf::Time time_delta;
    sf::Time time_acc;

    Scene *currentScene;
    Scene *nextScene;

    bool next;

    static Director *instance;

    Director(){};
    Director(Director const&){};

public:

    void initialize();

    static Director *getInstance();
    sf::RenderWindow *getWindow();

    void startWithScene(Scene *scene);
    void enqueueScene(Scene *scene);

};

#endif /* defined(__Ludum_Dare__Director__) */
