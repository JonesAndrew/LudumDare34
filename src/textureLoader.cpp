//
//  TextureLoader.cpp
//  GameClient
//
//  Created by Andrew Jones on 9/28/14.
//  Copyright (c) 2014 ThreeLives. All rights reserved.
//

#include "textureLoader.h"
#ifdef _WIN32
#else
#include "ResourcePath.hpp"
#endif
#include <iostream>

TextureLoader *TextureLoader::instance = NULL;

TextureLoader *TextureLoader::getInstance() {
    if (!instance) {
        instance = new TextureLoader();
    }
    return instance;
}

sf::Sprite TextureLoader::getSprite(std::string file) {
    Texture *tex = textures[file];

    if (tex == NULL) {
        tex = new Texture();
#ifdef _WIN32
        tex->tex.loadFromFile("../res/"+file);
        std::cout<<"../res/"+file<<"\n";
#else
        tex->tex.loadFromFile(resourcePath()+file);
#endif
        textures[file] = tex;
    }

    sf::Sprite sprite;
    sprite.setTexture(tex->tex);
    return sprite;
}

Animation TextureLoader::getAnim(std::string file) {
    Texture *tex = textures[file];

    if (tex == NULL) {
        tex = new Texture();
#ifdef _WIN32
        tex->tex.loadFromFile("../res/"+file);
        std::cout<<"../res/"+file<<"\n";
#else
        tex->tex.loadFromFile(resourcePath()+file);
#endif
        textures[file] = tex;
    }
    Animation anim;
    anim.setSpriteSheet(tex->tex);
    return anim;
}
