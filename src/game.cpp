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

void Game::makePlanet(sf::Vector2f pos, sf::Vector2f vel, int r) {
    std::shared_ptr<Planet> p = std::make_shared<Planet>();
    if (r == 0) {
        r=17;
        p->setSprite("Asteroid.png",r*2);
    } else if (r == 1) {
        r=31;
        p->setSprite("DumpPlanet.png",r*2);
    } else if (r == 2) {
        r=48;
        p->setSprite("Planet.png",r*2);
    } else {
        r=47;
        p->setSprite("MicroSun.png",192);
    }

    p->setRadius(r);
    p->setMass(r);
    p->setPos(pos);
    p->setVelocity(vel);
    p->setGame(this);

    planets.push_back(p);
    actors.push_back(planets.back());
}

void Game::start() {
    planets.clear();
    actors.clear();

    player = std::make_shared<Player>();
    player->setGame(this);
    actors.push_back(player);

    planets.push_back(std::make_shared<Planet>());
    planets.back()->setPos(sf::Vector2f(0,0));
    actors.push_back(planets.back());
    planets.back()->setVelocity(sf::Vector2f(0,0));
    planets.back()->setSprite("HomePlanet_1.png",100);

    player->setPlanet(planets.back());

    std::ifstream iFile("../res/"+std::to_string(round)+".txt");
    while (true) {
        std::string n;
        iFile >> n;
        if( iFile.eof() ) {
            std::cout << "break" << std::endl;
            break;
        }
        std::cout << n << std::endl;
        int x,y,velx,vely;
        iFile >> x >> y;
        std::cout << x << " " << y << std::endl;
        iFile >> velx >> vely;
        std::cout << velx << " " << vely << std::endl;
        int r;
        if (n == "MICROSUN") {
            r=3;
        } else if (n == "PLANET") {
            r=2;
        } else if (n == "DUMP") {
            r=1;
        } else {
            r=0;
        }
        makePlanet(sf::Vector2f(x,y),sf::Vector2f(velx/60.0,vely/60.0),r);
    }

    view.reset(sf::FloatRect(1280, 720, 1280, 720));
    view2.reset(sf::FloatRect(1280, 720, 1280, 720));
    view.setCenter(player->getPos());

    pressed = false;
    shake = winCount = 0;
    lose = false;
    hp=3;
}

void Game::setupScene(sf::RenderWindow *window) {
    srand(time(0));

    arrow = TextureLoader::getInstance()->getSprite("PlanetArrows.png");
    arrow.setTextureRect(sf::IntRect(0,0,24,24));
    arrow.setOrigin(sf::Vector2f(12,24));
    arrow.setScale(2,2);

    background = TextureLoader::getInstance()->getSprite("Background.png",true);
    background.setTextureRect(sf::IntRect(0,0,2048*16,2048*16));
    background.setPosition(-2048*8,-2048*8);

    winScreen = TextureLoader::getInstance()->getSprite("WaveWon.png");
    winScreen.setOrigin(84,48);

    shatter = TextureLoader::getInstance()->getAnim("Home.png");
    shatter.addFrame(sf::IntRect(0, 0, 120, 120));
    shatter.addFrame(sf::IntRect(120, 0, 120, 120));
    shatter.addFrame(sf::IntRect(240, 0, 120, 120));
    shatter.addFrame(sf::IntRect(0, 120, 120, 120));
    shatter.addFrame(sf::IntRect(120, 120, 120, 120));
    shatter.addFrame(sf::IntRect(240, 120, 120, 120));
    shatter.addFrame(sf::IntRect(0, 240, 120, 120));
    shatter.addFrame(sf::IntRect(120, 240, 120, 120));
    shatter.addFrame(sf::IntRect(240, 240, 120, 120));

    home.setOrigin(60,60);
    home.setLooped(false);

    round = 1;

    font.loadFromFile("../res/kenpixel.ttf");

    start();

    music.openFromFile("../res/mainsong.wav");
    music.setLoop(true);
    music.play();
}

void Game::draw(sf::RenderWindow *window) {
    home.update(sf::seconds(1.0/60.0));
    if (!lose) {
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

        if (winCount > 0) {
            winScreen.setPosition(640,160);
            window->draw(winScreen);
        }

        sf::Vector2f pos,size,diff;
        pos = view.getCenter();
        size = view.getSize();

        for (int i=0;i<planets.size();i++) {
            if (abs(planets[i]->getPos().x-view.getCenter().x) >= view.getSize().x/2+planets[i]->getRadius() || abs(planets[i]->getPos().y-view.getCenter().y) >= view.getSize().y/2+planets[i]->getRadius()) {
                diff = planets[i]->getPos()-view.getCenter();
                float angle = atan2 (diff.y,diff.x) * 180 / PI; //+ rand()%40/10.0-2.0;
                float x=-640;
                if (diff.x>0)
                x=640;
                float y=abs(x)*sin(angle*PI/180);

                float y2=-360;
                if (diff.y>0)
                y2=360;
                float x2=abs(y2)*cos(angle*PI/180);

                if (abs(y) < abs(x2)) {
                    arrow.setPosition(x+640,y+360);
                } else {
                    arrow.setPosition(x2+640,y2+360);
                }

                std::string f=planets[i]->getFile();
                if (planets[i]->home) {
                    arrow.setTextureRect(sf::IntRect(0,0,24,24));
                } else if (f=="Asteroid.png") {
                    arrow.setTextureRect(sf::IntRect(0,24,24,24));
                } else if (f=="MicroSun.png") {
                    arrow.setTextureRect(sf::IntRect(24,0,24,24));
                } else if (f=="DumpPlanet.png") {
                    arrow.setTextureRect(sf::IntRect(48,24,24,24));
                } else {
                    arrow.setTextureRect(sf::IntRect(48,0,24,24));
                }

                arrow.setRotation(angle-90);
                window->draw(arrow);
            }
        }
    } else {
        sf::Text text;

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("You Lose\nRestart?");

        // set the character size
        text.setCharacterSize(24);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top  + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(1280/2.0f,720/2.0f-260));

        home.setPosition(sf::Vector2f(1280/2.0f,720/2.0f));

        window->draw(home);
        window->draw(text);
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
    if (!lose) {
        if(winCount > 0) {
            winCount--;
            if (winCount == 1) {
                start();
            }
        }

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
            if (actors[i]->deadCount > 0) {
                for (int p=0;p<planets.size();p++) {
                    if (planets[p]->deadCount > 0) {
                        planets.erase(planets.begin()+p);
                        break;
                    }
                }
                if (actors[i]->deadCount == 1) {
                    actors.erase(actors.begin()+i);
                }
                i--;
            }
        }
        actors[0]->update();

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
                if (planets[i]->getFile() == "MicroSun.png" && player->deadCount == 0) {
                    player->deadCount = 60*60;
                    SoundPlayer::getInstance()->playSound("Death.wav");
                }
            } else if (player->getPlanet() != nullptr && player->getPlanet() != planets[i] && distance(player->getPos(),planets[i]->getPos()) < planets[i]->getRadius()+12 && player->deadCount == 0) {
                player->deadCount = 60*60;
                SoundPlayer::getInstance()->playSound("Death.wav");
            }
        }

        for (int i=0;i<planets.size(); i++) {
            for (int t=i+1;t<planets.size(); t++) {
                if(distance(planets[t]->getPos(),planets[i]->getPos()) < planets[i]->getRadius()+planets[t]->getRadius()) {
                    if (i == 0) {
                        if (abs(planets[t]->getPos().x-view.getCenter().x) <= view.getSize().x/2+planets[t]->getRadius() || abs(planets[t]->getPos().y-view.getCenter().y) <= view.getSize().y/2+planets[t]->getRadius()) {
                            if (planets[t]->getFile() == "Planet.png" || planets[t]->getFile() == "MicroSun.png") {
                                setShake(20);
                                hp-=2;
                            } else {
                                setShake(10);
                                hp-=1;
                            }
                            if(hp < 0) {
                                hp = 0;
                                lose=true;
                                home.play(shatter);
                            }
                            SoundPlayer::getInstance()->playSound("LargeCollide.wav");
                            planets[0]->setSprite("HomePlanet_"+std::to_string(4-hp)+".png",100);
                        }
                        planets[t]->deadCount = 2;
                        if (player->getPlanet() == planets[t]) {
                            player->setPlanet(nullptr);
                            sf::Vector2f c = planets[0]->getPos()-player->getPos();
                            float angle = atan2 (c.y,c.x) * 180 / PI; //+ rand()%40/10.0-2.0;
                            float x=cos(angle*PI/180);
                            float y=sin(angle*PI/180);
                            player->setVelocity(sf::Vector2f(x,y));
                        }
                    }  else if (planets[i]->getRadius() != planets[t]->getRadius()) {
                        if (planets[i]->getRadius() > planets[t]->getRadius()) {
                            planets[t]->deadCount = 2;
                            if (player->getPlanet() == planets[t]) {
                                player->setPlanet(nullptr);
                                sf::Vector2f c = planets[i]->getPos()-player->getPos();
                                float angle = atan2 (c.y,c.x) * 180 / PI; //+ rand()%40/10.0-2.0;
                                float x=cos(angle*PI/180);
                                float y=sin(angle*PI/180);
                                player->setVelocity(sf::Vector2f(x,y));
                            }
                        } else {
                            planets[i]->deadCount = 2;
                            if (player->getPlanet() == planets[i]) {
                                player->setPlanet(nullptr);
                                sf::Vector2f c = planets[t]->getPos()-player->getPos();
                                float angle = atan2 (c.y,c.x) * 180 / PI; //+ rand()%40/10.0-2.0;
                                float x=cos(angle*PI/180);
                                float y=sin(angle*PI/180);
                                player->setVelocity(sf::Vector2f(x,y));
                            }
                        }
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

        if (winCount == 0) {
            bool win=true;
            for (int i=1;i<planets.size(); i++) {
                sf::Vector2f c = planets[i]->getVelocity();
                float result = atan2 (c.y,c.x) * 180 / PI;
                c =  planets[i]->getPos()-planets[0]->getPos();
                result-= atan2 (c.y,c.x) * 180 / PI;
                if (abs(result) > 60) {
                    win = false;
                }
            }
            if(win) {
                round++;
                winCount = 60*3;
            }
        }

        float chase=0.06;
        view.setCenter(view.getCenter().x+(player->getPos().x-view.getCenter().x)*chase,view.getCenter().y+(player->getPos().y-view.getCenter().y)*chase);
        if (shake > 0) {
            view2.setCenter(view.getCenter());
            int angle = rand()%360;
            float x=cos(angle*PI/180)*shake;
            float y=sin(angle*PI/180)*shake;
            view2.move(x,y);
            shake-=0.4;
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
