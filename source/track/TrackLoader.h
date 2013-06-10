//
//  TrackLoader.h
//  Rac0r
//
//  Created by Jan Schulte on 03.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__TrackLoader__
#define __Rac0r__TrackLoader__

#include <iostream>
#include <vector>
#include <stdexcept>

#include <SFML/Graphics.hpp>


namespace Rac0r {
    
class TrackLoader {
    private:
        // how many points should be generated per curve
        constexpr static const unsigned int DEFAULT_CURVE_STEPS    =   10;
    
        // curve roation
        enum class Curve_Rotation { COUNTER_CLOCK_WISE = 0, CLOCK_WISE = 1 };
    
    public:
        TrackLoader();
        ~TrackLoader();
    
        // load the given track file
        std::vector<sf::Vector2f> loadFromFile(const std::string & _fileName);
    
        // properties
        void setCurveSteps(unsigned int _delta) { this->mCurveSteps = _delta; if (_delta == 0) { this->mCurveSteps = TrackLoader::DEFAULT_CURVE_STEPS; } }
        float getCurveSteps() const { return this->mCurveSteps; }
    
    private:
        void computeCurve(Curve_Rotation _roation, float _degree, const sf::Vector2f & _point, const sf::Vector2f & _dir, std::vector<sf::Vector2f> & _result);
        sf::Vector2f computeCurvePivot(const sf::Vector2f & _point, const sf::Vector2f & _dir);
    
    private:
        unsigned int   mCurveSteps;
};

}


#endif /* defined(__Rac0r__TrackLoader__) */
