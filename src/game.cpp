//
//  Game.cpp
//  Ludum Dare
//
//  Created by Andrew Jones on 8/22/14.
//  Copyright (c) 2014 Andrew Jones. All rights reserved.
//

#include <fstream>
#include "game.h"
#include "planet.h"
#include "player.h"
#include "director.h"
#include "textureLoader.h"
#include "sound.h"
#ifdef _WIN32
#else
#include "ResourcePath.hpp"
#endif

#define PI 3.14159265

sf::Vector2f normalize(const sf::Vector2f& source)
{
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
    return sf::Vector2f(source.x / length, source.y / length);
    else
    return source;
}

float distance(sf::Vector2f a, sf::Vector2f b) {
    sf::Vector2f c=a-b;
    return sqrt(c.x*c.x+c.y*c.y);
}

void Game::start() {
    actors.clear();

    player = std::make_shared<Player>();
    player->setGame(this);
    actors.push_back(player);

    rects.emplace_back(0,700,1280,20);
    wall.setFillColor(sf::Color(255,255,255));
}

void Game::setupScene(sf::RenderWindow *window) {
    start();
}

void Game::draw(sf::RenderWindow *window) {
    for (int i=0; i<actors.size(); i++) {
        window->draw(*actors[i]);
    }
    for (int i=0;i<rects.size();i++) {
      wall.setPosition(rects[i].left,rects[i].top);
      wall.setSize(sf::Vector2f(rects[i].white, rects[i].height));
      window->draw(wall);
    }
}

void Game::handleEvent(sf::Event event, sf::RenderWindow *window) {
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::R)
        {
            start();
        }
    }
}

bool Game::tick(sf::RenderWindow *window) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (pressed == false) {
            player->jump();
            pressed = true;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        player->moveLeft();
        pressed = false;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        player->moveRight();
        pressed = false;
    } else {
        pressed = false;
    }
    for (int i=0; i<actors.size(); i++) {
        actors[i]->update();
    }

    for (int i=0;i<rects.size();i++) {
      if (rects[i].contains(player->getPos())) {
        player->setPos(sf::Vector2f(player->getPos().x,rects[i].top));
        player->grounded = true;
        player->dj = true;
      }
    }

    return true;
}
