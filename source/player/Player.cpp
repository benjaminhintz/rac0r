//
//  Player.cpp
//  Rac0r
//
//  Created by Jan Schulte on 18.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "Player.h"


namespace Rac0r {
  
Player::Player(Car * _car, sf::Keyboard::Key _key) :
    mCar(_car),
    mLapCount(0),
    mLapTime(0),
    mTotalTime(0),
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

    this->mCar->update(_elapsed);
}
    
void Player::reset() {
    this->mLapCount = 0;
    this->mLapTime = 0;
    this->mTotalTime = 0;
}

void Player::resetToLastValidPosition() {
    this->mCar->resetToLastValidPosition();
}

void Player::accelerate() {
    if (this->mLapCount < Constants::GAME_MAX_LAPS) {
        mCar->accelerate();
    }
}



}

