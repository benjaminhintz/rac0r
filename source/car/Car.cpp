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
    
Car::Car(const Track & _track, CarEventListener * _eventListener) :
    mTrack(_track),
    mEventListener(_eventListener),
    mLocation(_track[Track::START_INDEX]),
    mDirection(1.0f, 0.0f),
    mVelocity(0.0f),
    mForce(0.0f),
    mSegmentStart(Track::START_INDEX),
    mSegmentEnd(Track::START_INDEX),
    mCarDrawable(sf::Vector2f(Car::CAR_WIDTH, Car::CAR_HEIGHT))
{
    this->mCarDrawable.setOrigin(Car::CAR_WIDTH / 2.0f, Car::CAR_HEIGHT / 2.0f);
}


void Car::update(const sf::Time & _time) {
    
    // compute cars offset to the track segment and adjust it
    sf::Vector2f proj = project(this->mLocation, this->mTrack[this->mSegmentStart], this->mTrack[this->mSegmentEnd]);
    sf::Vector2f positionAdjust = proj - this->mLocation;
   
    // apply drag friction
    if (this->mVelocity > 0.0f) {
        this->mForce -= abs(Car::FRICTION_FORCE * (this->mVelocity));
    }
    
    // compute acceleration A = F / M
    float acceleration = this->mForce / Car::DEFAULT_MASS;
    //std::cout << "Acceleration: " << acceleration << std::endl;
    
    // compute velocity
    this->mVelocity += acceleration * _time.asSeconds();
    this->mVelocity = fmax(fmin(this->mVelocity, Car::MAX_VELOCITY), 0.0f);
    //this->mVelocitiy += this->mDirection * (acceleration * _time.asSeconds());
    //std::cout << "Velocity: " << this->mVelocity << std::endl;
        
    // compute new position
    this->mLocation += this->mDirection * (this->mVelocity * _time.asSeconds());
    //this->mLocation += this->mVelocitiy * _time.asSeconds();
    this->mLocation += positionAdjust;
    
    // keep car on the track
    this->keepOnTrack();
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
    this->mForce = Car::ACCELERATION_FORCE;
}

void Car::resetToStart() {
    this->mSegmentStart = Track::START_INDEX;
    this->mSegmentEnd = Track::START_INDEX;
    this->mLocation = this->mTrack[this->mSegmentStart];
    this->mDirection = sf::Vector2f(1.0f, 0.0f);
    this->mVelocity = 0.0f;
    this->mForce = 0.0f;
}

void Car::keepOnTrack() {
    
    // find next track segment
    size_t startIndex = 0;
    size_t endIndex = 0;
    if (this->mTrack.findSegment(this->mLocation, this->mSegmentStart, startIndex, endIndex) && endIndex != this->mSegmentEnd) {
    
        //std::cout << "Old Segment (Start: " << this->mSegmentStart << ", End: " << this->mSegmentEnd << std::endl;
        //std::cout << "New Segment found (Start: " << startIndex << ", End: " << endIndex << std::endl;
        
        // Debug Stuff
        this->mLocationPoint = sf::CircleShape(2);
        this->mLocationPoint.setPosition(this->mLocation);
        this->mLocationPoint.setOrigin(1, 1);
        this->mLocationPoint.setFillColor(sf::Color::Blue);
        
        this->mNextLocationPoint = sf::CircleShape(2);
        this->mNextLocationPoint.setPosition(this->mTrack[endIndex]);
        this->mNextLocationPoint.setOrigin(1, 1);
        this->mNextLocationPoint.setFillColor(sf::Color::Blue);
        
        // Important stuff ;)
        if (startIndex == 0 && endIndex == 1 && this->mSegmentStart == this->mTrack.size()-1 && this->mEventListener != NULL) {
            this->mEventListener->onCarMovedThroughStart(*this);
        }
        this->mDirection = normalize(this->mTrack[endIndex] - this->mTrack[this->mSegmentStart]);
        this->mSegmentStart = this->mSegmentEnd;
        this->mSegmentEnd = endIndex;
        
        //std::cout << "Current Segment (Start: " << this->mSegmentStart << ", End: " << this->mSegmentEnd << std::endl;
        
        

    }
 
    // Debug Stuff
    float len = length(this->mDirection * this->mVelocity * 0.1f);
    //float len = length(this->mDirection * 100.0f);
    this->mDirectionShape = sf::RectangleShape(sf::Vector2f(len, 2));
    this->mDirectionShape.setPosition(this->mLocation);
    this->mDirectionShape.setOrigin(0, 1);
    this->mDirectionShape.setRotation(RAD_TO_DEG(heading(this->mDirection)));
    this->mDirectionShape.setFillColor(sf::Color::Green);
    //std::cout << "Velo: " << this->mVelocitiy << " - Len: " << len << std::endl;
}
    

}

