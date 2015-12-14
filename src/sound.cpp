#include "sound.h"

SoundPlayer *SoundPlayer::instance = NULL;

SoundPlayer *SoundPlayer::getInstance() {
    if (!instance) {
        instance = new SoundPlayer();
    }
    return instance;
}

void SoundPlayer::playSound(std::string file) {
    for (int i=0; i<sfx.size(); i++) {
        if (sfx[i].getStatus() == sf::Sound::Stopped) {
            sfx.erase(sfx.begin()+i);
            i--;
        }
    }

    Sound *s = sounds[file];

    if (s == NULL) {
        s = new Sound();
#ifdef _WIN32
        s->s.loadFromFile("../res/"+file);
        std::cout<<"../res/"+file<<"\n";
#else
        tex->tex.loadFromFile(resourcePath()+file);
#endif
        sounds[file] = s;
    }

    sfx.emplace_back();
    sfx.back().setBuffer(s->s);
    sfx.back().play();
}
