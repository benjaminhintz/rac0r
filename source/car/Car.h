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
        constexpr static const float            MAX_VELOCITY            =   1000.0f;
        constexpr static const float            ACCELERATION_FORCE      =   600.0f;
        constexpr static const float            FRICTION_FORCE          =   0.05;
        constexpr static const float            DEFAULT_MASS            =   1.0f;
   
    public:
        Car(const Track &_track);
    
        // update & render the car
        void update(const sf::Time & _time);
        void draw(sf::RenderTarget & _target, const sf::RenderStates & _states = sf::RenderStates::Default);
    
        // accelerate the car
        void accelerate();
    
        // reset car to start position
        void reset();
    
        // properties
        void setColor(const sf::Color & _value) { this->mCarDrawable.setFillColor(_value); }
        const sf::Color & getColor() const { return this->mCarDrawable.getFillColor(); }
    
    private:
        void keepOnTrack();
       
    private:
        // track handling
        const Track&            mTrack;
        size_t                  mSegmentStart;
        size_t                  mSegmentEnd;
    
        // physics handling
        sf::Vector2f            mLocation;
        sf::Vector2f            mDirection;
        float                   mVelocity;
        float                   mForce;
  
        // visual handling
        sf::RectangleShape      mCarDrawable;
    
        // Debug Stuff
        sf::CircleShape         mLocationPoint;
        sf::CircleShape         mNextLocationPoint;
        sf::RectangleShape      mDirectionShape;
};

}


#endif /* defined(__Rac0r__Car__) */
