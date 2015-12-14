#include "planet.h"
#include "game.h"

#define PI 3.14159265

Planet::Planet() {
    radius = 50;
    velocity = sf::Vector2f(0.2,0.37);
    mass = 60;
    deadCount = 0;
    home = false;
}

void Planet::draw(sf::RenderTarget &target, sf::RenderStates) const {
    target.draw(sprite);
}

int Planet::getRadius() {
    return radius;
}

int Planet::getMass() {
    return mass;
}

void Planet::setMass(int m) {
    mass = m;
}

void Planet::setRadius(int r) {
    radius = r;
}

void Planet::update() {
    Actor::update();
    sprite.update(sf::seconds(1.0/60.0));
    if (deadCount == 1 && file == "DumpPlanet.png") {
        float angle = atan2 (velocity.y,velocity.x) * 180 / PI; //+ rand()%40/10.0-2.0;
        float x=cos((angle+90)*PI/180)*20;
        float y=sin((angle+90)*PI/180)*20;
        float vx=cos((angle+45)*PI/180)*1.5;
        float vy=sin((angle+45)*PI/180)*1.5;
        game->makePlanet(sf::Vector2f(x+pos.x,y+pos.y),sf::Vector2f(vx,vy),0);
        x=cos((angle-90)*PI/180)*20;
        y=sin((angle-90)*PI/180)*20;
        vx=cos((angle-45)*PI/180)*1.5;
        vy=sin((angle-45)*PI/180)*1.5;
        game->makePlanet(sf::Vector2f(x+pos.x,y+pos.y),sf::Vector2f(vx,vy),0);
    }
}

void Planet::setSprite(std::string f, int size) {
    file = f;
    if (file == "HomePlanet_1.png") {
        home = true;
    }
    sprite.stop();
    anim.emplace_back(TextureLoader::getInstance()->getAnim(file));
    anim.back().addFrame(sf::IntRect(0, 0, size-1, size-1));
    if (file == "MicroSun.png") {
        anim.back().addFrame(sf::IntRect(192, 0, size-1, size-1));
        anim.back().addFrame(sf::IntRect(192*2, 0, size-1, size-1));
        anim.back().addFrame(sf::IntRect(192*3, 0, size-1, size-1));
    }
    sprite.setOrigin(size/2-1,size/2-1);
    sprite.play(anim.back());
    sprite.setLooped(true);
}

void Planet::setVelocity(sf::Vector2f a) {
    if (home == false) {
        velocity = a;
    }
}

std::string Planet::getFile() {
    return file;
}

Planet::~Planet() {
    if (game) {
        game = nullptr;
    }
}
