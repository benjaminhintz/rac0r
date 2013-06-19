//
//  Player.cpp
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

#include "Player.h"


namespace Rac0r {
  
sf::Clock Player::mClock = sf::Clock();

Player::Player(Car * _car, sf::Keyboard::Key _key) :
    mCar(_car),
    mLapCount(0),
    mLapTime(0),
    mTotalTime(0),
    mIsFinish(false),
    mKey(_key)
{
}

Player::~Player() {
    delete this->mCar;
}

void Player::draw(sf::RenderTarget & _target, sf::RenderStates _states) const {

    _target.draw(*this->mCar, _states);
}

void Player::update(sf::Time _elapsed) {
    
    if (sf::Keyboard::isKeyPressed(this->mKey)) {
    	this->accelerate();
    }

    if (!this->mCar->isOnTrack()) {
        if (this->mDriftedOffTrackTime == 0) {
            this->mDriftedOffTrackTime = mClock.getElapsedTime().asMilliseconds();
        } else {
            size_t diff = mClock.getElapsedTime().asMilliseconds() - this->mDriftedOffTrackTime;
            if (diff >= Constants::PLAYER_OFF_TRACK_RESET_INTERVAL) {
                this->resetToLastValidPosition();
            }
        }
    }
    
    this->mCar->update(_elapsed);
    
    this->mLapTime = mClock.getElapsedTime().asMilliseconds() - this->mTotalTime;
    //std::cout << "Lap Time: " << this->mLapTime << std::endl;
}
    
void Player::reset() {
    this->mLapCount = 0;
    this->mLapTime = 0;
    this->mTotalTime = 0;
    this->mIsFinish = false;
}

void Player::resetToLastValidPosition() {
    this->mCar->resetToLastValidPosition();
    this->mDriftedOffTrackTime = 0;
}

void Player::accelerate() {
    if (this->mLapCount < Constants::GAME_MAX_LAPS) {
        mCar->accelerate();
    }
}

void Player::nextLap() {
    this->mLapCount++;
    this->mLapTime = 0;
    this->mTotalTime = mClock.getElapsedTime().asMilliseconds();
    
    if (this->mLapCount >= Constants::GAME_MAX_LAPS) {
        this->mIsFinish = true;
    }
}



}

