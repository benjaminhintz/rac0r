//
//  Player.h
//  Rac0r
//
//  Created and copyright by
//  Benjamin Hintz
//  Florian Kaluschke
//  Jannes Meyer
//  David Leska
//  Lars Peterke
//  Jan Schulte
//  on Jun 2013. All rights reserved.
//

#ifndef __Rac0r__Player__
#define __Rac0r__Player__

#include <iostream>

#include "../car/Car.h"

namespace Rac0r {

class Player {
    public:
        Player(Car * _car, sf::Keyboard::Key _key);
        ~Player();
    
        void draw(sf::RenderTarget & _target, sf::RenderStates _states) const;
        void update(sf::Time _elapsed);

        Car * getCar() { return mCar; };

        void nextLap();
        size_t getCurrentLap() const { return mLapCount; };

        void setTotalTime(size_t _time) { mTotalTime = _time;}
        size_t getTotalTime() const { return mTotalTime; }

        void setLapTime(size_t _time) { mLapTime = _time;}
        size_t getLapTime() const { return mLapTime; }
    
        void setDriftedOffTrackTime(size_t _time) { mDriftedOffTrackTime = _time;}
        size_t getDriftedOffTrackTime() const { return mDriftedOffTrackTime; }

        bool isFinish() const { return this->mIsFinish; }
    
        sf::Keyboard::Key getKey() const { return mKey; }

        void accelerate();
        void reset();
        void resetToLastValidPosition();
    
    private:
        Car*                    mCar;
        size_t                  mLapCount;
        size_t                  mLapTime;
        size_t                  mTotalTime;
        size_t                  mDriftedOffTrackTime;
        bool                    mIsFinish;
    
        sf::Keyboard::Key       mKey;
    
        static sf::Clock        mClock;
};


}

#endif /* defined(__Rac0r__Player__) */
