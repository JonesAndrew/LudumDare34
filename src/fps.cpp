#include "fps.hpp"

void FPS::update()
{
    if(mClock.getElapsedTime().asSeconds() >= 1.f)
    {
        std::cout << "fps:" << mFrame << std::endl;
        mFps = mFrame;
        mFrame = 0;
        mClock.restart();
    }

    ++mFrame;
}
