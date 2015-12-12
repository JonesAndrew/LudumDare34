#include <SFML/Graphics.hpp>
#include "game.h"
#include "director.h"

int main()
{
    Game *scene = new Game();
    Director::getInstance()->initialize();
    Director::getInstance()->startWithScene(scene);
    return EXIT_SUCCESS;
}
