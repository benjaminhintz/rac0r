//
//  Car.h
//  Rac0r
//
//  Created and copyright by
//  Jan Schulte
//  David Leska
//  Benjamin Hintz
//  Florian Kaluschke
//  Lars Peterke
//  Jannes Meyer
//  on Jun 2013. All rights reserved.
//

#ifndef __Rac0r__Car__
#define __Rac0r__Car__

#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "../game/GameConstants.h"
#include "../track/Track.h"


namespace Rac0r {

// forwards
class Car;

#ifndef __linux
typedef std::shared_ptr<Car>    shared_car;
#endif


class CarEventListener {
    public:
        CarEventListener() { }
        
        virtual void onCarDriftedOffTrack(Rac0r::Car & _car) = 0;
        virtual void onCarMovedThroughStart(Rac0r::Car & _car) = 0;
        virtual void onCarStartedFromStart(Rac0r::Car & _car) = 0;
};


class Car : public sf::Drawable {
    public:
        // physics constants
        constexpr static const float            MAX_VELOCITY            =   1000.0f;
        constexpr static const float            MAX_ANGULAR_VELOCITY    =   120.0f;
        constexpr static const float            ACCELERATION_FORCE      =   600.0f;
        constexpr static const float            FRICTION_FORCE          =   0.04f;
        constexpr static const float            DRAG_FRICTION_OFF_TRACK =   0.6f;
        constexpr static const float            BREAK_FRICTION          =   0.09f;
    
        constexpr static const float            DEFAULT_MASS            =   1.0f;
   
        // car shape constants
        constexpr static const float            CAR_WIDTH               =   30.0f;
        constexpr static const float            CAR_HEIGHT              =   10.0f;
   
        // car ghost constants
        constexpr static const size_t           MAX_GHOSTS              =   30;
        constexpr static const float            MAX_GHOSTS_DISTANCE     =   4.0f;
        constexpr static const size_t           MAX_GHOSTS_AGE          =   80;   // miliseconds
    
   
    public:
        Car(const Track &_track, CarEventListener * _eventListener);
        
        // update & render the car
        void update(const sf::Time & _time);
        virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
    
        // accelerate the car
        void accelerate();
    
        // reset car to start position
        void resetToStart();
        // reset car to last valid position
        void resetToLastValidPosition();
    
        // properties
        void setColor(const sf::Color & _value) { this->mCarDrawable.setFillColor(_value); }
        const sf::Color & getColor() const { return this->mCarDrawable.getFillColor(); }
    
        void setEventListener(CarEventListener * _value) { this->mEventListener = _value; }
        CarEventListener * getEventListener() const { return this->mEventListener; }
    
        float getPassedDistance() const { return this->mCurrentPassedDistance; }
        // This is only used from the outside after the game has finished
        void setPassedDistance(float distance) { this->mCurrentPassedDistance = distance; }
    
        bool isOnTrack() const { return !this->mDriftedOffTrack; }
    
    private:
        void keepOnTrack();
        void updateGhosts();
    
    private:
        struct Ghost {
            sf::RectangleShape  ghost;
            size_t              age;
            
            Ghost(const sf::RectangleShape & _ghost, size_t _age) : ghost(_ghost), age(_age) { }
        };
    
    private:
        // event handling
        CarEventListener*                   mEventListener;
    
        // track handling
        const Track&                        mTrack;
        size_t                              mSegmentStart;
        size_t                              mSegmentEnd;
        size_t                              mLastValidSegmentStart;
        size_t                              mLastValidSegmentEnd;
    
        // physics handling
        sf::Vector2f                        mCurrentLocation;
        sf::Vector2f                        mLastLocation;
        sf::Vector2f                        mCurrentDirection;
        sf::Vector2f                        mLastDirection;
        float                               mVelocity;
        float                               mForce;
        float                               mCurrentPassedDistance;
        float                               mLastPassedDistance;
        float                               mCurrentSpeed;
        bool                                mDriftedOffTrack;
        bool                                mCarStartedFromStart;
        bool                                mIsAccelerating;
    
        // visual handling
        sf::RectangleShape                  mCarDrawable;
        std::list<Ghost>                    mCarGhostDrawables;
    
        // Debug Stuff
        sf::CircleShape                     mLocationPoint;
        sf::CircleShape                     mNextLocationPoint;
        sf::RectangleShape                  mDirectionShape;
};

}

#endif /* defined(__Rac0r__Car__) */
