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
        typedef std::vector<sf::Vector2f>   Points;
    
    public:
        Track();
        Track(const Points & _points, const std::string & _name, const std::string & _author);
    
        // properties
        void setPoints(const Points & _value);
        const Points & getPoints() const { return this->mPoints; }
    
        void setName(const std::string & _value) { this->mName = _value; }
        const std::string & getName() const { return this->mName; }
    
        void setAuthor(const std::string & _value) { this->mAuthor = _value; }
        const std::string & getAuthor() const { return this->mAuthor; }
    
    private:
        void computeBounds();
    
    private:
        Points             mPoints;
        sf::Vector2f        mBounds[2]; // top-left, bottom-right
        std::string         mName;
        std::string         mAuthor;
    
};
    
}

#endif /* defined(__Rac0r__Track__) */
