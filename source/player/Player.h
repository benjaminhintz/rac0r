//
//  Player.h
//  Rac0r
//
//  Created by Jan Schulte on 18.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__Player__
#define __Rac0r__Player__

#include <iostream>

#include "Car.h"

namespace Rac0r {

class Player {
    public:
        Player(Car * _car, sf::Keyboard::Key _key);
        ~Player();
    
        void draw(sf::RenderTarget & _target, sf::RenderStates _states) const;
        void update(sf::Time _elapsed);
   
        void accelerate();
        void reset();
        void resetToLastValidPosition();
    
    private:
        Car*                    mCar;
        size_t                  mLapCount;
        size_t                  mLapTime;
        size_t                  mTotalTime;
        sf::Keyboard::Key       mKey;
};


}

#endif /* defined(__Rac0r__Player__) */
