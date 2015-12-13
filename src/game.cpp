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

#define PI 3.14159265

float distance(sf::Vector2f a, sf::Vector2f b) {
    sf::Vector2f c=a-b;
    return sqrt(c.x*c.x+c.y*c.y);
}

void Game::setupScene(sf::RenderWindow *window) {
    player = std::make_shared<Player>();
    actors.push_back(player);
    planets.push_back(std::make_shared<Planet>());
    actors.push_back(planets.back());
    player->setPlanet(planets.back());
    planets.push_back(std::make_shared<Planet>());
    planets.back()->setPos(sf::Vector2f(300,100));
    actors.push_back(planets.back());

    planets.push_back(std::make_shared<Planet>());
    planets.back()->setPos(sf::Vector2f(600,400));
    actors.push_back(planets.back());
    planets.back()->setVelocity(sf::Vector2f(0,0));
    view.reset(sf::FloatRect(1280, 720, 1280/2, 720/2));
    view.setCenter(player->getPos());

    pressed = false;
}

void Game::draw(sf::RenderWindow *window) {
    window->setView(view);

    for (int i=0; i<actors.size(); i++) {
        window->draw(*actors[i]);
    }

    // restore the default view
    window->setView(window->getDefaultView());
}

void Game::handleEvent(sf::Event event, sf::RenderWindow *window) {
}

bool Game::tick(sf::RenderWindow *window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
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
    for (int i=0;i<planets.size(); i++) {
        if(player->getPlanet() == nullptr && distance(player->getPos(),planets[i]->getPos()) < planets[i]->getRadius()+2) {
            sf::Vector2f c = player->getPos()-planets[i]->getPos();
            float result = atan2 (c.y,c.x) * 180 / PI;
            player->setAngle(result);
            player->setPlanet(planets[i]);
        }
    }
    float chase=0.075;//distance(player->getPos(),view.getCenter());
    view.setCenter(view.getCenter().x+(player->getPos().x-view.getCenter().x)*chase,view.getCenter().y+(player->getPos().y-view.getCenter().y)*chase);
    fps.update();
    return true;
}
