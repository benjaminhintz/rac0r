//
//  vector2.h
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

#ifndef Rac0r_vector2_h
#define Rac0r_vector2_h

#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>

    
#define DEG_TO_RAD(x) (x) * (M_PI / 180.0f)
#define RAD_TO_DEG(x) (x) * (180.0f / M_PI)


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

// min
template <typename T>
sf::Vector2<T> min(const sf::Vector2<T> & _a, T _b) {
    return sf::Vector2f(fmin(_a.x, _b), fmin(_a.y, _b));
}

template <typename T>
sf::Vector2<T> max(const sf::Vector2<T> & _a, T _b) {
    return sf::Vector2f(fmax(_a.x, _b), fmin(_a.y, _b));
}

template <typename T>
sf::Vector2<T> operator * (const sf::Vector2<T> & _a, const sf::Vector2<T> & _b) {
    return sf::Vector2<T>(_a.x * _b.x, _a.y * _b.y);
}

// limit the given vector _a to the given length _b
template <typename T>
sf::Vector2<T> limit(const sf::Vector2<T> & _a, T _b) {

    float len = length(_a);
    if (len > _b) {
        sf::Vector2<T> result = normalize(_a);
        result *= _b;
        return result;
    }
    return _a;
}

template <typename T>
T heading(const sf::Vector2<T> & _a) {
    return -atan2(-_a.y, _a.x);
}

template <typename T>
T heading2(const sf::Vector2<T> & _a, const sf::Vector2<T> & _b) {
    return acos(scalar(_a, _b));
}

template <typename T>
sf::Vector2<T> project(const sf::Vector2<T> & _p, const sf::Vector2<T> & _a, const sf::Vector2<T> & _b) {

    sf::Vector2f ap = _p - _a;
    sf::Vector2f ab = _b - _a;
    
    ab = normalize(ab);
    ab *= scalar(ap, ab);
    
    return _a + ab;
}



// overload steam output for the vector class
template <typename T>
std::ostream & operator << (std::ostream & _out, const sf::Vector2<T> & _vector) {
    _out << "x:" << _vector.x << ", y:" << _vector.y;
    return _out;
}


    
} // end namespace
    
#endif
