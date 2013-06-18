//
//  Header.h
//  Rac0r
//
//  Created by Lars Peterke on 18.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include <vector>

#ifndef Rac0r_Header_h
#define Rac0r_Header_h

#include "game/Game.h"

namespace Rac0r {
    
    class SoundMgr {
    public:
        SoundMgr();
        ~SoundMgr() { for(auto obj : bgm) delete obj; }
        void play(size_t track) { stop(); if(Rac0r::Constants::PLAY_SOUND) { if(track < bgm.size()) bgm.at(track)->play(); } }
        void stop() { for(sf::Music* obj : bgm) obj->stop(); }
    private:
        static const size_t SOUNDS_NUM = 2;
        const std::string SOUNDS[SOUNDS_NUM] = { "menu.ogg", "race.ogg" };
        std::vector<sf::Music*> bgm;
    };
}


#endif
