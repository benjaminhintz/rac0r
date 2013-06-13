//
//  Car.cpp
//  Rac0r
//
//  Created by Jan Schulte on 11.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "Car.h"


#include "../utils/vector2.h"


namespace Rac0r {
    
Car::Car(const Track & _track) :
    mTrack(_track),
    mLocation(_track[Track::START_INDEX]),
    mDirection(1.0f, 0.0f),
    mVelocitiy(0.0f, 0.0f),
    mAcceleration(0.0f),
    mTrackIndex(Track::START_INDEX),
    mAccelerate(false),
    mCarDrawable(sf::Vector2f(30.0f, 10.0f))
{
    this->mCarDrawable.setOrigin(15.0f, 5.0f);
}


void Car::update(const sf::Time & _time) {
    
    // find next track segment
    size_t newIndex = 0;
    if (this->mTrack.findClosestPoint(this->mLocation, newIndex) && newIndex != this->mTrackIndex) {
        this->applyDirection(newIndex);
    }
    
    this->mVelocitiy = this->mDirection * (this->mAcceleration * _time.asSeconds());
    this->mVelocitiy = limit(this->mVelocitiy, Car::MAX_SPEED);
    
    this->mLocation += this->mVelocitiy;
    
    this->decelerate();
    
    this->mAccelerate = false;
}


void Car::draw(sf::RenderTarget & _target, const sf::RenderStates & _states) {
    
    // compute rotation
    float angle = heading(this->mDirection);
    
    this->mCarDrawable.setRotation(RAD_TO_DEG(angle));
    this->mCarDrawable.setPosition(this->mLocation);
    
    _target.draw(this->mCarDrawable, _states);
}
    
void Car::accelerate() {
    
    this->mAcceleration += Car::ACCELERATION_STEP;
    this->mAcceleration = fmax(this->mAcceleration, Car::MAX_SPEED);
}

void Car::decelerate() {

    this->mAcceleration -= Car::DECELERATION_STEP;
    if (this->mAcceleration  < 0.0f) {
        this->mAcceleration = 0.0f;
    }
}

void Car::applyDirection(size_t _trackIndex) {
    
    this->mDirection = normalize(this->mTrack[_trackIndex] - this->mLocation); // TODO: Evlt. 
    this->mTrackIndex = _trackIndex;
}
    

}

