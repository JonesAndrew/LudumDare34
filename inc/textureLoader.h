//
//  TextureLoader.h
//  GameClient
//
//  Created by Andrew Jones on 9/28/14.
//  Copyright (c) 2014 ThreeLives. All rights reserved.
//

#ifndef __GameClient__TextureLoader__
#define __GameClient__TextureLoader__

#include <iostream>
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"

struct Texture {
    sf::Texture tex;
    int refCount;
};

class TextureLoader {
private:

    std::map<std::string, Texture*> textures;

    static TextureLoader *instance;

    TextureLoader(){};
    TextureLoader(TextureLoader const&){};

public:

    static TextureLoader *getInstance();
    sf::Sprite getSprite(std::string file);
    Animation getAnim(std::string file);
};

#endif /* defined(__GameClient__TextureLoader__) */
