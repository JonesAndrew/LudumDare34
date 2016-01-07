#include "player.h"
#include <math.h>
#include "game.h"
#include "sound.h"

#define PI 3.14159265

#define DELAY 6

float distance2(sf::Vector2f a, sf::Vector2f b) {
    sf::Vector2f c=a-b;
    return sqrt(c.x*c.x+c.y*c.y);
}

void Player::update() {
  velocity.y += 0.1;

  if (velocity.x > 0) {
    velocity.x -= 0.3;
  } else {
    velocity.x += 0.3;
  }

  if (abs(velocity.x) < 0.4) {
    velocity.x = 0;
  }

  if (velocity.y > 5) {
    velocity.y = 5;
  }
  if (velocity.x < -3) {
    velocity.x = -3;
  }
  if (velocity.x > 3) {
    velocity.x = 3;
  }

  pos+=velocity;
}

Player::Player() {
  pos=sf::Vector2f(200,200);
  sprite.setSize(sf::Vector2f(50, 50));
  sprite.setOrigin(25,50);
  sprite.setFillColor(sf::Color(255,255,255));
}

void Player::jump() {
  if (grounded || dj) {
    if (grounded) {
      dj = false;
    }
    grounded = false;
    velocity.y = -4;
  }
}

void Player::moveLeft() {
  velocity.x -= 0.4;
}

void Player::moveRight() {
  velocity.x += 0.4;
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates) const {
    target.draw(sprite);
}

Player::~Player() {
}
