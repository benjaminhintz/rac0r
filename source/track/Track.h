//
//  Track.h
//  Rac0r
//
//  Created by Jan Schulte on 10.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__Track__
#define __Rac0r__Track__

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#include <SFML/Graphics.hpp>

namespace Rac0r {
    
class Track {
    public:
        typedef std::vector<sf::Vector2f>       Points;
    
        constexpr static const size_t           START_INDEX     =   0;
    
    public:
        Track();
        Track(const Points & _points, const std::string & _name, const std::string & _author);
    
        // properties
        void setPoints(const Points & _value);
        const Points & getPoints() const { return this->mPoints; }
        size_t size() const { return this->mPoints.size(); }
        const sf::Vector2f & operator[] (size_t _index) const; // NOTE: Circular Version
        bool findClosestPoint(const sf::Vector2f & _location, size_t & _foundIndex) const;
    
        void setScale(float _value, bool _respectCurveDirection = true);
        float getScale() const { return this->mScale; }
        void scaleToFitBounds(const sf::Vector2f _value, bool _respectCurveDirection = true, float _adjustValue = 0.0f);
    
        void setCenter(const sf::Vector2f & _value);
        const sf::Vector2f & getCenter() const { return this->mCenter; }
    
        void setName(const std::string & _value) { this->mName = _value; }
        const std::string & getName() const { return this->mName; }
    
        void setAuthor(const std::string & _value) { this->mAuthor = _value; }
        const std::string & getAuthor() const { return this->mAuthor; }
    
    private:
        void computeBounds();
    
    private:
        Points              mPoints;
        sf::Vector2f        mBounds[2]; // top-left, bottom-right
        sf::Vector2f        mCenter;
        float               mScale;
        std::string         mName;
        std::string         mAuthor;
    
};
    
}

#endif /* defined(__Rac0r__Track__) */