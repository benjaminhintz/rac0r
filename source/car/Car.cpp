//
//  Car.cpp
//  Rac0r
//
//  Created by Jan Schulte on 11.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "Car.h"


#include "../utils/vector2.h"

// LINK: http://natureofcode.com/book/chapter-6-autonomous-agents/

namespace Rac0r {
    
Car::Car(const Track & _track) :
    mTrack(_track),
    mLocation(_track[Track::START_INDEX]),
    mVelocitiy(0.0f, 0.0f),
    mAcceleration(0.0f, 0.0f),
    mTrackIndex(Track::START_INDEX),
    mCarDrawable(sf::Vector2f(30.0f, 10.0f))
{
    this->mCarDrawable.setOrigin(15.0f, 5.0f);
}


void Car::update(const sf::Time & _time) {
    
    this->mVelocitiy += this->mAcceleration * 20.0f * _time.asSeconds();
    this->mVelocitiy = limit(this->mVelocitiy, Car::MAX_SPEED);
    
    this->mLocation += this->mVelocitiy;
    
    this->mAcceleration *= 0.0f;
    
    // TEST
    size_t newIndex = 0;
    if (mTrack.findClosestPoint(this->mLocation, newIndex) && newIndex != this->mTrackIndex) {
        this->mTrackIndex = newIndex;
        std::cout << "Current Index: (" << this->mTrackIndex << ")" << std::endl;
    
        this->steerTorwards(this->mTrack[this->mTrackIndex]);
    }
    
}


void Car::draw(sf::RenderTarget & _target, const sf::RenderStates & _states) {
    
    // compute rotation
    float angle = heading(this->mVelocitiy);
    
    this->mCarDrawable.setRotation(RAD_TO_DEG(angle));
    this->mCarDrawable.setPosition(this->mLocation);
    
    _target.draw(this->mCarDrawable, _states);
}
    
void Car::accelerate() {
    
    //this->mForce = fmin(this->mForce += 1.0f, Car::MAX_FORCE);
}

void Car::steerTorwards(const sf::Vector2f & _target) {

    std::cout << "Current Location: (" << this->mLocation << ")" << std::endl;
    std::cout << "New Location: (" << _target << ")" << std::endl;
    
    sf::Vector2f desired = normalize(_target - this->mLocation);
    
    desired *= Car::MAX_SPEED;
    
    sf::Vector2f steer = desired - this->mVelocitiy;
    //steer = limit(steer, Car::MAX_FORCE); // this->mForce);
    
    this->applyForce(steer);
}
    
void Car::applyForce(const sf::Vector2f & _force) {
    sf::Vector2f force = limit(_force, Car::MAX_FORCE);
    
    std::cout << "Force: (" << _force << ")" << std::endl;
    
    this->mAcceleration += force;
}

    

}

