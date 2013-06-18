//
//  Player.h
//  Rac0r
//
//  Created and copyright by
//  Benjamin Hintz
//  Florian Kaluschke
//  David Leska
//  Lars Peterke
//  Jan Schulte
//  on Jun 2013. All rights reserved.
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
