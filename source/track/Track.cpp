//
//  Track.cpp
//  Rac0r
//
//  Created by Jan Schulte on 10.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "Track.h"

#include <cfloat>

#include "../utils/vector2.h"

namespace Rac0r {
 
Track::Track() :
    Track(Points(), "Undefined", "Undefined")
{
}

Track::Track(const Points & _points, const std::string & _name, const std::string & _author) :
    mPoints(_points),
    mName(_name),
    mAuthor(_author)
{
    this->computeBounds();
}
  
void Track::setPoints(const Points & _value) {
    
    this->mPoints = _value;
    
    this->computeBounds();
}

void Track::setCenter(const sf::Vector2f & _value) {
    sf::Vector2f offset = _value - this->mCenter;
    for (auto & point : this->mPoints) {
        point += offset;
    }
}


void Track::computeBounds() {

    this->mBounds[0] = sf::Vector2f(FLT_MAX, FLT_MAX); // top-left
    this->mBounds[1] = sf::Vector2f(FLT_MIN, FLT_MIN); // bottom_right
    
    for (auto & point : this->mPoints) {
        this->mBounds[0].x = fmin(point.x, this->mBounds[0].x);
        this->mBounds[0].y = fmin(point.y, this->mBounds[0].y);
        this->mBounds[1].x = fmax(point.x, this->mBounds[1].x);
        this->mBounds[1].y = fmax(point.y, this->mBounds[1].y);
    }
 
    this->mCenter = (this->mBounds[0] + this->mBounds[1]) / 2.0f;
    
    std::cout << "Track Center: Center(" << this->mCenter << ")" << std::endl;
    std::cout << "Track Bounds: Top-Left(" << this->mBounds[0] << ") - Bottom-Right(" << this->mBounds[1] << ")" << std::endl;
}


}