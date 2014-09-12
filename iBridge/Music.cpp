
#ifndef __iBridge__Music__
#define __iBridge__Music__

#include <iostream>
#include "SimpleAudioEngine.h"

using namespace std;

class Music {
public:
        Music(string path);
        void play();
private:
        string music;
};

#endif /* defined(__iBridge__Music__) */
