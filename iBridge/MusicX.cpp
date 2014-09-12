//
//  Music.cpp
//  iBridge
//
//  Created by Tianlin Shi on 1/11/13.
//
//

#include "Music.h"

Music::Music(string path) {
        this->music = path;
}

void Music::play() {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(music.c_str(), true);
}