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

void Game::makePlanet(int dist) {
    std::shared_ptr<Planet> p = std::make_shared<Planet>();
    int r = rand()%40+25;
    if (r <= 50) {
        r=17;
        p->setSprite("Asteroid.png",r*2);
    } else {
        r=48;
        p->setSprite("Planet.png",r*2);
    }
    p->setRadius(r);
    p->setMass(r);

    float angle = rand()%360;

    p->setPos(sf::Vector2f(sf::Vector2f(0,dist*sin(angle*PI/180))+sf::Vector2f(dist*cos(angle*PI/180),0)));

    for (int i=0;i<planets.size()-1; i++) {
        if(distance(p->getPos(),planets[i]->getPos()) < planets[i]->getRadius()+p->getRadius()) {
            return;
        }
    }

    sf::Vector2f c = p->getPos()-planets[0]->getPos();
    angle = atan2 (c.y,c.x) * 180 / PI; //+ rand()%40/10.0-2.0;
    float x=cos(angle*PI/180);
    float y=sin(angle*PI/180);

    p->setVelocity(sf::Vector2f(x*((rand()%15/10)-0.75),y*((rand()%15/10)-0.75)));

    planets.push_back(p);
    actors.push_back(planets.back());
}

void Game::setupScene(sf::RenderWindow *window) {
    srand(time(0));

    background = TextureLoader::getInstance()->getSprite("Background.png",true);
    background.setTextureRect(sf::IntRect(0,0,2048*16,2048*16));
    background.setPosition(-2048*8,-2048*8);

    player = std::make_shared<Player>();
    player->setGame(this);
    actors.push_back(player);

    planets.push_back(std::make_shared<Planet>());
    planets.back()->setPos(sf::Vector2f(0,0));
    actors.push_back(planets.back());
    planets.back()->setVelocity(sf::Vector2f(0,0));
    planets.back()->setSprite("HomePlanet.png",100);

    player->setPlanet(planets.back());

    for (int i=0; i<200; i++) {
        makePlanet(200+rand()%400+70*i);
    }

    view.reset(sf::FloatRect(1280, 720, 1280/2, 720/2));
    view2.reset(sf::FloatRect(1280, 720, 1280/2, 720/2));
    view.setCenter(player->getPos());

    pressed = false;
    shake = 0;
    pause = false;

    music.openFromFile("../res/song.wav");
    music.setLoop(true);
    music.play();
}

void Game::draw(sf::RenderWindow *window) {
    if (shake > 0) {
        window->setView(view2);
    } else {
        window->setView(view);
    }

    window->draw(background);

    for (int i=0; i<actors.size(); i++) {
        window->draw(*actors[i]);
    }

    // restore the default view
    window->setView(window->getDefaultView());
}

void Game::handleEvent(sf::Event event, sf::RenderWindow *window) {
}

bool Game::tick(sf::RenderWindow *window) {
    if (!pause) {
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
        for (int i=1; i<actors.size(); i++) {
            actors[i]->update();
            if (actors[i]->dead) {
                actors.erase(actors.begin()+i);
                for (int p=0;p<planets.size();p++) {
                    if (planets[p]->dead) {
                        planets.erase(planets.begin()+p);
                        break;
                    }
                }
                i--;
            }
        }
        actors[0]->update();

        while (planets.size() < 200) {
            makePlanet(200+rand()%400+70*100);
        }

        int dist = 2;
        if (player->getFreeze() < -6 && player->getPlanet() == nullptr) {
            dist = 6;
        }

        for (int i=0;i<planets.size(); i++) {
            if(player->getPlanet() == nullptr && distance(player->getPos(),planets[i]->getPos()) < planets[i]->getRadius()+dist) {
                sf::Vector2f c = player->getPos()-planets[i]->getPos();
                float result = atan2 (c.y,c.x) * 180 / PI;
                player->setAngle(result);
                player->setPlanet(planets[i]);
            } else if (player->getPlanet() != nullptr && player->getPlanet() != planets[i] && distance(player->getPos(),planets[i]->getPos()) < planets[i]->getRadius()+12) {
                pause = true;
            }
        }

        for (int i=0;i<planets.size(); i++) {
            for (int t=i+1;t<planets.size(); t++) {
                if(distance(planets[t]->getPos(),planets[i]->getPos()) < planets[i]->getRadius()+planets[t]->getRadius()) {
                    if (i == 0) {
                        planets[t]->dead = true;
                    } else {
                        sf::Vector2f axis1,axis2;
                        sf::Vector2f vel1 = planets[i]->getVelocity();
                        sf::Vector2f vel2 = planets[t]->getVelocity();
                        sf::Vector2f pos1 = planets[i]->getPos();
                        sf::Vector2f pos2 = planets[t]->getPos();
                        double m1 = planets[i]->getMass();
                        double m2 = planets[t]->getMass();

                        double  m21,dvx2,a,x21,y21,vx21,vy21,fy21,sign,vx_cm,vy_cm;

                        m21=m2/m1;
                        x21=pos2.x-pos1.x;
                        y21=pos2.y-pos1.y;
                        vx21=vel2.x-vel1.x;
                        vy21=vel2.y-vel1.y;

                        a=y21/x21;
                        dvx2= -2*(vx21 +a*vy21)/((1+a*a)*(1+m21)) ;
                        vel2.x=vel2.x+dvx2;
                        vel2.y=vel2.y+a*dvx2;
                        vel1.x=vel1.x-m21*dvx2;
                        vel1.y=vel1.y-a*m21*dvx2;

                        planets[i]->setVelocity(vel1);
                        planets[t]->setVelocity(vel2);
                    }
                }
            }
        }

        float chase=0.075;
        view.setCenter(view.getCenter().x+(player->getPos().x-view.getCenter().x)*chase,view.getCenter().y+(player->getPos().y-view.getCenter().y)*chase);
        if (shake > 0) {
            view2.setCenter(view.getCenter());
            int angle = rand()%360;
            float x=cos(angle*PI/180)*shake;
            float y=sin(angle*PI/180)*shake;
            view2.move(x,y);
            shake-=0.4;
            std::cout<<"angle: "<<angle<<"\n";
        } else {
            shake = 0;
        }
    }
    fps.update();
    return true;
}

void Game::setShake(float s) {
    shake = s;
    view2.setCenter(view.getCenter());
}
