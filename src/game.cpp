//
//  Game.cpp
//  Ludum Dare
//
//  Created by Andrew Jones on 8/22/14.
//  Copyright (c) 2014 Andrew Jones. All rights reserved.
//

#include "game.h"
#include "textureLoader.h"
#ifdef _WIN32
#else
#include "ResourcePath.hpp"
#endif

void Game::setupScene(sf::RenderWindow *window) {

}

void Game::draw(sf::RenderWindow *window) {
    window->draw(a);
}

void Game::handleEvent(sf::Event event, sf::RenderWindow *window) {
}

bool Game::tick(sf::RenderWindow *window) {
    return true;
}
