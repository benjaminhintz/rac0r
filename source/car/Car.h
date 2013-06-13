//
//  Car.h
//  Rac0r
//
//  Created by Jan Schulte on 11.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__Car__
#define __Rac0r__Car__

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../track/Track.h"


namespace Rac0r {
    
class Car {
    public:
        constexpr static const float            MAX_SPEED           =   6.0f;
        constexpr static const float            ACCELERATION_STEP   =   10.0f;
        constexpr static const float            DECELERATION_STEP   =   1.0f;
   
    public:
        Car(const Track &_track);
    
        void update(const sf::Time & _time);
        void draw(sf::RenderTarget & _target, const sf::RenderStates & _states = sf::RenderStates::Default);
    
        void accelerate();
        void decelerate();
    
        void reset();
    
        // properties
        void setColor(const sf::Color & _value) { this->mCarDrawable.setFillColor(_value); }
        const sf::Color & getColor() const { return this->mCarDrawable.getFillColor(); }
    
    private:
        void applyDirection(size_t _trackIndex);
        //void steerTorwards(const sf::Vector2f & _target);
        void applyForce(const sf::Vector2f & _force);
    
    private:
        const Track&            mTrack;
        
        sf::Vector2f            mLocation;
        sf::Vector2f            mDirection;
        sf::Vector2f            mVelocitiy;
        float                   mAcceleration;
        size_t                  mTrackIndex;
        size_t                  mNextTrackIndex;
        bool                    mAccelerate;
        sf::RectangleShape      mCarDrawable;
    
        // Debug Stuff
        sf::CircleShape         mLocationPoint;
        sf::CircleShape         mNextLocationPoint;
        sf::RectangleShape      mDirectionShape;
};

}


#endif /* defined(__Rac0r__Car__) */
