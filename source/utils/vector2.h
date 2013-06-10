//
//  vector2.h
//  Rac0r
//
//  Created by Jan Schulte on 02.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef Rac0r_vector2_h
#define Rac0r_vector2_h

#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>


namespace Rac0r {
    
// computes the vector length
template <typename T>
    float length(const sf::Vector2<T> & _vector) {
    return sqrt((_vector.x * _vector.x) + (_vector.y * _vector.y));
}

    
// normalizes the given vector
template <typename T>
sf::Vector2<T> normalize(const sf::Vector2<T> & _vector) {
    float len = length(_vector);
    if (len != 0.0f) {
        return sf::Vector2<T>(_vector.x / len, _vector.y / len);
    } else {
        return _vector;
    }
}

// compute the orthonal of the given vector
template <typename T>
    sf::Vector2<T> orthogonal(const sf::Vector2<T> & _vector) {
    return sf::Vector2<T>(_vector.y, -_vector.x);
}

// computes the scalar of the two given vectors
template <typename T>
float scalar(const sf::Vector2<T> & _a, const sf::Vector2<T> & _b) {
    return _a.x * _b.x + _a.y * _b.y;
}

// compute the angle between the two given vectors
template <typename T>
float angle(const sf::Vector2<T> & _a, const sf::Vector2<T> & _b) {
    float len1 = length(_a);
    float len2 = length(_b);
    
    return scalar(_a, _b) / (len1 * len2);
}

// compute the slope defining by the two vectors
template <typename T>
float slope(const sf::Vector2<T> & _a, const sf::Vector2<T> & _b) {
    return (_b.y - _a.y) / (_b.x - _a.x);
}


template <typename T>
sf::Vector2<T> operator * (sf::Vector2<T> & _a, sf::Vector2<T> & _b) {
    return sf::Vector2<T>(_a.x * _b.x, _a.y * _b.y);
}

// overload steam output for the vector class
template <typename T>
std::ostream & operator << (std::ostream & _out, const sf::Vector2<T> & _vector) {
    _out << "x:" << _vector.x << ", y:" << _vector.y;
    return _out;
}


    
} // end namespace
    
#endif
