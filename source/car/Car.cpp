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
    mNextTrackIndex(Track::START_INDEX),
    mAccelerate(false),
    mCarDrawable(sf::Vector2f(30.0f, 10.0f))
{
    this->mCarDrawable.setOrigin(15.0f, 5.0f);
}


void Car::update(const sf::Time & _time) {
    
    // find next track segment
    size_t newIndex = 0;
    if (this->mTrack.findClosestPoint(this->mTrackIndex, this->mLocation + this->mVelocitiy, newIndex) && newIndex != this->mNextTrackIndex) {
        this->applyDirection(newIndex);
    }
    
    sf::Vector2f proj = project(this->mLocation, this->mTrack[this->mTrackIndex], this->mTrack[this->mNextTrackIndex]);
    sf::Vector2f dir = proj - this->mLocation;
    //std::cout << "Dir: " << dir << std::endl;
    
    this->mVelocitiy = this->mDirection * (this->mAcceleration * _time.asSeconds());
    this->mVelocitiy = limit(this->mVelocitiy, Car::MAX_SPEED);
    
    this->mLocation += this->mVelocitiy + dir;
    
    this->decelerate();
    
    this->mAccelerate = false;
    
     
}


void Car::draw(sf::RenderTarget & _target, const sf::RenderStates & _states) {
    
    // compute rotation
    float angle = heading(this->mDirection);
    
    this->mCarDrawable.setRotation(RAD_TO_DEG(angle));
    this->mCarDrawable.setPosition(this->mLocation);
    
    _target.draw(this->mCarDrawable, _states);
    
    // Debug Stuff
    this->mLocationPoint.setPosition(this->mLocation);
    _target.draw(this->mLocationPoint, _states);
    _target.draw(this->mNextLocationPoint, _states);
    this->mDirectionShape.setPosition(this->mLocation);
    _target.draw(this->mDirectionShape, _states);
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

void Car::reset() {
    this->mTrackIndex = Track::START_INDEX;
    this->mNextTrackIndex = Track::START_INDEX;
    this->mLocation = this->mTrack[this->mTrackIndex];
    this->mDirection = sf::Vector2f(1.0f, 0.0f);
    this->mVelocitiy = sf::Vector2f(0.0f, 0.0f);
    this->mAcceleration = 0.0f;
}

void Car::applyDirection(size_t _trackIndex) {
    
    // Debug Stuff
    this->mLocationPoint = sf::CircleShape(2);
    this->mLocationPoint.setPosition(this->mLocation);
    this->mLocationPoint.setOrigin(1, 1);
    this->mLocationPoint.setFillColor(sf::Color::Blue);
    
    this->mNextLocationPoint = sf::CircleShape(2);
    this->mNextLocationPoint.setPosition(this->mTrack[_trackIndex]);
    this->mNextLocationPoint.setOrigin(1, 1);
    this->mNextLocationPoint.setFillColor(sf::Color::Blue);
    
    
    this->mDirection = normalize(this->mTrack[_trackIndex] - this->mTrack[this->mTrackIndex]);
    this->mTrackIndex = this->mNextTrackIndex;
    this->mNextTrackIndex = _trackIndex;
    

    // DEBUG
    //float len = length(this->mDirection * length(this->mVelocitiy)) * 100.0f;
    float len = length(this->mDirection * 100.0f);
    this->mDirectionShape = sf::RectangleShape(sf::Vector2f(len, 2));
    this->mDirectionShape.setPosition(this->mLocation);
    this->mDirectionShape.setOrigin(0, 1);
    this->mDirectionShape.setRotation(RAD_TO_DEG(heading(this->mDirection)));
    this->mDirectionShape.setFillColor(sf::Color::Green);
    //std::cout << "Velo: " << this->mVelocitiy << " - Len: " << len << std::endl;
    
}
    

}

