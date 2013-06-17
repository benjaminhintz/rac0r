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
    mCurrentLocation(_track[Track::START_INDEX]),
    mLastLocation(mCurrentLocation),
    mCurrentDirection(1.0f, 0.0f),
    mLastDirection(1.0f, 0.0f),
    mVelocity(0.0f),
    mForce(0.0f),
    mDriftedOffTrack(false),
    mCarStartedFromStart(false),
    mSegmentStart(Track::START_INDEX),
    mSegmentEnd(Track::START_INDEX),
    mCarDrawable(sf::Vector2f(Car::CAR_WIDTH, Car::CAR_HEIGHT))
{
    this->mCarDrawable.setOrigin(Car::CAR_WIDTH / 2.0f, Car::CAR_HEIGHT / 2.0f);
}

void Car::update(const sf::Time & _time) {
    
    // keep location as last valid
    if (!this->mDriftedOffTrack) {
        this->mLastLocation = this->mCurrentLocation;
    }
    
    // compute cars offset to the track segment and adjust it
    sf::Vector2f proj = project(this->mCurrentLocation, this->mTrack[this->mSegmentStart], this->mTrack[this->mSegmentEnd]);
    sf::Vector2f positionAdjust = proj - this->mCurrentLocation;
   
    // apply drag friction
    if (this->mVelocity > 0.0f) {
        this->mForce -= abs(Car::FRICTION_FORCE * (this->mVelocity) * (this->mDriftedOffTrack ? 4.0f : 1.0f));
    }
    
    // compute acceleration A = F / M
    float acceleration = this->mForce / Car::DEFAULT_MASS;
    //std::cout << "Acceleration: " << acceleration << std::endl;
    
    // compute velocity
    this->mVelocity += acceleration * _time.asSeconds();
    this->mVelocity = fmax(fmin(this->mVelocity, Car::MAX_VELOCITY), 0.0f);
    //std::cout << "Velocity: " << this->mVelocity << std::endl;
        
    // compute new position
    this->mCurrentLocation += this->mCurrentDirection * (this->mVelocity * _time.asSeconds());
    this->mCurrentLocation += positionAdjust;
    
    // keep car on the track
    this->keepOnTrack();
    
    // update ghosts
    this->updateGhosts();
    
    // compute rotation
    float angle = heading(this->mCurrentDirection);
    
    this->mCarDrawable.setRotation(RAD_TO_DEG(angle));
    this->mCarDrawable.setPosition(this->mCurrentLocation);
    
    // debug stuff
    this->mLocationPoint.setPosition(this->mCurrentLocation);
    this->mDirectionShape.setPosition(this->mCurrentLocation);
}

void Car::draw(sf::RenderTarget& _target, sf::RenderStates _states) const {
    // draw ghosts
    for (auto & ghost : this->mCarGhostDrawables) {
        _target.draw(ghost.ghost, _states);
    }
    
    _target.draw(this->mCarDrawable, _states);
    
    // Debug Stuff
    /*
    _target.draw(this->mLocationPoint, _states);
    _target.draw(this->mNextLocationPoint, _states);
    _target.draw(this->mDirectionShape, _states);
    */
}
    
void Car::accelerate() {
    if (!this->mDriftedOffTrack) {
        this->mForce = Car::ACCELERATION_FORCE;
    }
}

void Car::resetToStart() {
    this->mSegmentStart = Track::START_INDEX;
    this->mSegmentEnd = Track::START_INDEX;
    this->mCurrentLocation = this->mTrack[this->mSegmentStart];
    this->mCurrentDirection = normalize(this->mTrack[this->mSegmentEnd] - this->mTrack[this->mSegmentStart]);
    this->mLastDirection = this->mCurrentDirection;
    this->mVelocity = 0.0f;
    this->mForce = 0.0f;
    this->mDriftedOffTrack = false;
    this->mCarStartedFromStart = false;
}

void Car::resetToLastValidPosition() {
    this->mCurrentDirection = normalize(this->mTrack[this->mSegmentEnd] - this->mTrack[this->mSegmentStart]);
    this->mLastDirection = this->mCurrentDirection;
    this->mCurrentLocation = this->mLastLocation;
    this->mVelocity = 0.0f;
    this->mForce = 0.0f;
    this->mDriftedOffTrack = false;
}

void Car::keepOnTrack() {
    
    // find next track segment
    size_t startIndex = 0;
    size_t endIndex = 0;
    if (!this->mDriftedOffTrack && this->mTrack.findSegment(this->mCurrentLocation, this->mSegmentStart, startIndex, endIndex) && endIndex != this->mSegmentEnd) {
    
        //std::cout << "Old Segment (Start: " << this->mSegmentStart << ", End: " << this->mSegmentEnd << std::endl;
        //std::cout << "New Segment found (Start: " << startIndex << ", End: " << endIndex << std::endl;
        
        // Debug Stuff
        this->mLocationPoint = sf::CircleShape(2);
        this->mLocationPoint.setPosition(this->mCurrentLocation);
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
        
        this->mLastDirection = this->mCurrentDirection;
        this->mCurrentDirection = normalize(this->mTrack[endIndex] - this->mTrack[this->mSegmentStart]);
        this->mSegmentStart = this->mSegmentEnd;
        this->mSegmentEnd = endIndex;
        
        //std::cout << "Current Segment (Start: " << this->mSegmentStart << ", End: " << this->mSegmentEnd << std::endl;
    }
    
    // check for car start
    if (!this->mCarStartedFromStart && startIndex == 0 && endIndex == 1 && this->mSegmentStart == 0 && this->mVelocity > 0.0f && this->mEventListener != NULL) {
        this->mCarStartedFromStart = true;
        this->mEventListener->onCarStartedFromStart(*this);
    }
    
    // check if we drift of the track
    sf::Vector2f moveDir = normalize(this->mCurrentLocation * this->mCurrentDirection);
    sf::Vector2f trackDir = normalize(this->mLastDirection);
    float angularSpeed = length(moveDir - trackDir) * this->mVelocity;
    if (!this->mDriftedOffTrack && angularSpeed >= Car::MAX_ANGULAR_VELOCITY && this->mEventListener != NULL) {
        this->mDriftedOffTrack = true;
        this->mEventListener->onCarDriftedOffTrack(*this);
    }
    
    // Debug Stuff
    //float len = length(this->mDirection * 100.0f);
    this->mDirectionShape = sf::RectangleShape(sf::Vector2f(angularSpeed, 2));
    this->mDirectionShape.setPosition(this->mCurrentLocation);
    this->mDirectionShape.setOrigin(0, 1);
    this->mDirectionShape.setRotation(RAD_TO_DEG(heading(moveDir - trackDir)));
    if (angularSpeed >= Car::MAX_ANGULAR_VELOCITY) {
        this->mDirectionShape.setFillColor(sf::Color::Red);
    } else if (angularSpeed >= Car::MAX_ANGULAR_VELOCITY * 0.5f) {
        this->mDirectionShape.setFillColor(sf::Color::Yellow);
    } else {
        this->mDirectionShape.setFillColor(sf::Color::Green);
    }

}
    
void Car::updateGhosts() {
    static sf::Clock clock = sf::Clock();
    
    sf::Time time = clock.getElapsedTime();
    
    sf::Vector2f lastLocation = this->mLastLocation;
    if (this->mCarGhostDrawables.size() > 0) {
        //std::list<Ghost>::iterator it = this->mCarGhostDrawables.back()
        lastLocation = this->mCarGhostDrawables.back().ghost.getPosition();
    }
    
    // add new ghost
    float ghostDistance = length(this->mCurrentLocation - lastLocation);
    if (ghostDistance >= Car::MAX_GHOSTS_DISTANCE && this->mVelocity > 0.0f) {
        sf::RectangleShape ghost(sf::Vector2f(Car::CAR_WIDTH, Car::CAR_HEIGHT));
        ghost.setOrigin(Car::CAR_WIDTH / 2.0f, Car::CAR_HEIGHT / 2.0f);
        
        sf::Vector2f dir = normalize(this->mCurrentDirection);
        ghost.setPosition(this->mCurrentLocation); // - (dir * (Car::MAX_GHOSTS_DISTANCE + 20.0f)));
        ghost.setRotation(RAD_TO_DEG(heading(dir)));
        
        ghost.setFillColor(this->mCarDrawable.getFillColor());
        
        this->mCarGhostDrawables.push_back(Ghost(ghost, time.asMilliseconds()));
        
        if (this->mCarGhostDrawables.size() >= Car::MAX_GHOSTS) {
            this->mCarGhostDrawables.erase(this->mCarGhostDrawables.begin());
        }
    }
    
    // do we need to remove some ghosts?
    std::list<Ghost>::iterator it = this->mCarGhostDrawables.begin();
    while (it != this->mCarGhostDrawables.end()) {
        if ((time.asMilliseconds() - (*it).age) >= Car::MAX_GHOSTS_AGE) {
            it = this->mCarGhostDrawables.erase(it);
        } else {
            ++it;
        }
    }
       
    // adjust alphas
    int i = this->mCarGhostDrawables.size()+1;
    //float steps = (80.0f - (80.0f * (MAX_VELOCITY / this->mVelocity))) / static_cast<float>(i);
    float steps = 80.0f / static_cast<float>(i);
    sf::Color color = this->mCarDrawable.getFillColor();
    for (std::list<Ghost>::reverse_iterator it = this->mCarGhostDrawables.rbegin(); it != this->mCarGhostDrawables.rend(); ++it) {
        color.a = steps * i--;
        (*it).ghost.setFillColor(color);
    }

}

}

