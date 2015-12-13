#include "planet.h"

Planet::Planet() {
    radius = 50;
    velocity = sf::Vector2f(0.2,0.37);
    mass = 60;
    dead = false;
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
    if (pos.x > 14500 || pos.x < -14500 || pos.y > 14500 || pos.y < -14500) {
        dead = true;
    }
}

void Planet::setSprite(std::string file, int size) {
    if (file == "HomePlanet.png") {
        home = true;
    }
    anim = TextureLoader::getInstance()->getAnim(file);
    anim.addFrame(sf::IntRect(0, 0, size-1, size-1));
    sprite.setOrigin(size/2,size/2);
    sprite.play(anim);
}

void Planet::setVelocity(sf::Vector2f a) {
    if (home == false) {
        velocity = a;
    }
}
