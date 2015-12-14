//
//  Game.h
//  Ludum Dare
//
//  Created by Andrew Jones on 8/22/14.
//  Copyright (c) 2014 Andrew Jones. All rights reserved.
//

#ifndef __Ludum_Dare__Game__
#define __Ludum_Dare__Game__

#include "scene.h"
#include "actor.h"
#include "Player.h"
#include <TGUI/TGUI.hpp>
#include <SFML/Network.hpp>
#include "fps.hpp"

class Game : public Scene {
    sf::Sprite background;
    sf::Sprite winScreen;
    sf::View view,view2;
    std::vector<std::shared_ptr<Actor>> actors;
    FPS fps;
    std::shared_ptr<Player> player;
    bool pressed;
    float shake;
    sf::Music music;
    sf::Sprite arrow;
    int hp,round;
    int winCount;
    sf::Font font;
    bool lose;
    AnimatedSprite home;
    Animation shatter;
public:
    std::vector<std::shared_ptr<Planet>> planets;
    virtual void draw(sf::RenderWindow *window);
    virtual void setupScene(sf::RenderWindow *window);
    virtual bool tick(sf::RenderWindow *window);
    virtual void handleEvent(sf::Event event, sf::RenderWindow *window);
    void makePlanet(sf::Vector2f,sf::Vector2f,int);
    void setShake(float s);
    void start();
};

#endif /* defined(__Ludum_Dare__Game__) */
