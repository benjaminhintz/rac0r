//
//  TrackLoader.h
//  Rac0r
//
//  Created and copyright by
//  Benjamin Hintz
//  Florian Kaluschke
//  David Leska
//  Lars Peterke
//  Jan Schulte
//  on Jun 2013. All rights reserved.
//

#ifndef __Rac0r__TrackLoader__
#define __Rac0r__TrackLoader__

#include "Track.h"

namespace Rac0r {

class TrackLoader {
    private:
        // how many points should be generated per curve
        constexpr static const unsigned int DEFAULT_CURVE_STEPS    =   10; // TODO: 40+ Um so ungenauer wird es an den Enden der Kurve?????
    
        // curve roation
        enum class Curve_Rotation { COUNTER_CLOCK_WISE = 0, CLOCK_WISE = 1 };
    
    public:
        TrackLoader();
        ~TrackLoader();
    
        // load the given track file
        Track loadFromFile(const std::string & _fileName);
    
        // properties
        void setCurveSteps(unsigned int _value) { this->mCurveSteps = _value; if (_value == 0) { this->mCurveSteps = TrackLoader::DEFAULT_CURVE_STEPS; } }
        float getCurveSteps() const { return this->mCurveSteps; }
    
    private:
        void computeCurve(Curve_Rotation _roation, float _degree, const sf::Vector2f & _point, const sf::Vector2f & _dir, Track::Points & _result);
        
    private:
        unsigned int        mCurveSteps;
        
};

}


#endif /* defined(__Rac0r__TrackLoader__) */
