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
	static constexpr const float            MAX_SPEED   =   8.0f;
	static constexpr const float            MAX_FORCE   =   10.0f;
   
    public:
        Car(const Track &_track);
    
        void update(const sf::Time & _time);
        void draw(sf::RenderTarget & _target, const sf::RenderStates & _states = sf::RenderStates::Default);
    
        void accelerate();
    
        // properties
        void setColor(const sf::Color & _value) { this->mCarDrawable.setFillColor(_value); }
        const sf::Color & getColor() const { return this->mCarDrawable.getFillColor(); }
    
    private:
        void steerTorwards(const sf::Vector2f & _target);
        void applyForce(const sf::Vector2f & _force);
    
    private:
        const Track&            mTrack;
        
        sf::Vector2f            mLocation;
        sf::Vector2f            mVelocitiy;
        sf::Vector2f            mAcceleration;
        float                   mForce;
        size_t                  mTrackIndex;
    
        sf::RectangleShape      mCarDrawable;
    
};

}


#endif /* defined(__Rac0r__Car__) */
