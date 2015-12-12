//
//  Director.cpp
//  Ludum Dare
//
//  Created by Andrew Jones on 8/22/14.
//  Copyright (c) 2014 Andrew Jones. All rights reserved.
//

#include "director.h"

Director *Director::instance = NULL;

Director *Director::getInstance() {
    if (!instance) instance = new Director();
    return instance;
}

void Director::initialize() {
    window.create(sf::VideoMode(800, 600), "Strat");
    window.setVerticalSyncEnabled(true);

    timer.restart();
}

void Director::startWithScene(Scene *scene) {
    nextScene = scene;

    do {

        currentScene = nextScene;
            time_now = timer.getElapsedTime();
            time_delta = time_now - time_old;
            time_old = time_now;

        currentScene->setupScene(getWindow());

        next = false;

        bool running = true;
        bool redraw = true;

        while (running) {
            time_now = timer.getElapsedTime();
            time_delta = time_now - time_old;
            time_old = time_now;

            if (time_delta.asMilliseconds() > 500)
                time_delta = sf::milliseconds(500);

            time_acc += time_delta;

            if (time_acc.asMilliseconds() >= 1000.0/60.0) {
                running = currentScene->tick(getWindow());

                redraw = true;

                time_acc = sf::milliseconds(time_acc.asMilliseconds()-1000.0/60);
            } else {
                sf::sleep(time_acc-sf::milliseconds(2));
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed) {
                    window.close();
                    running = false;
                } else {
                    currentScene->handleEvent(event, getWindow());
                }
            }

            if (redraw) {
                window.clear();
                currentScene->draw(getWindow());
                window.display();
                redraw = false;
            }
        }
    } while (next);

}

sf::RenderWindow *Director::getWindow() {
    return &window;
}

void Director::enqueueScene(Scene *scene) {
    next = true;
    nextScene = scene;
}
