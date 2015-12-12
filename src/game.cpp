//
//  Game.cpp
//  Ludum Dare
//
//  Created by Andrew Jones on 8/22/14.
//  Copyright (c) 2014 Andrew Jones. All rights reserved.
//

#include "game.h"
#include "planet.h"
#include "player.h"
#include "textureLoader.h"
#ifdef _WIN32
#else
#include "ResourcePath.hpp"
#endif

void Game::setupScene(sf::RenderWindow *window) {
    player = std::make_shared<Player>();
    actors.push_back(player);
    planets.push_back(std::make_shared<Planet>());
    actors.push_back(planets.back());
    player->setPlanet(planets.back());
}

void Game::draw(sf::RenderWindow *window) {
    player->setAngle(player->getAngle()+1);
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
    return true;
}
