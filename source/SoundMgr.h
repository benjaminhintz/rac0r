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

namespace Rac0r {
    
    class SoundMgr {
    public:
        SoundMgr();
        void play(size_t track) { bgm.at(track)->play(); }
        void stop(size_t track) { bgm.at(track)->stop(); }
    private:
        std::vector<sf::Music*> bgm;
    };
}


#endif
