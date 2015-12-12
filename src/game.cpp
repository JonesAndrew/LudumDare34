//
//  Game.cpp
//  Ludum Dare
//
//  Created by Andrew Jones on 8/22/14.
//  Copyright (c) 2014 Andrew Jones. All rights reserved.
//

#include "game.h"
#include "planet.h"
#include "textureLoader.h"
#ifdef _WIN32
#else
#include "ResourcePath.hpp"
#endif

void Game::setupScene(sf::RenderWindow *window) {
    actors.push_back(std::make_shared<Planet>());
}

void Game::draw(sf::RenderWindow *window) {
    for (int i=0; i<actors.size(); i++) {
        window->draw(*actors[i]);
    }
}

void Game::handleEvent(sf::Event event, sf::RenderWindow *window) {
}

bool Game::tick(sf::RenderWindow *window) {
    for (int i=0; i<actors.size(); i++) {
        actors[i]->update();
    }
    fps.update();
    std::cout << "fps:" << fps.getFPS() << std::endl;
    return true;
}
