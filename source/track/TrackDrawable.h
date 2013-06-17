//
//  Track.h
//  Rac0r
//
//  Created by Jan Schulte on 02.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__TrackLine__
#define __Rac0r__TrackLine__

#include <iostream>
#include <vector>
#include <stdexcept>

#include <SFML/Graphics.hpp>

#include "Track.h"


namespace Rac0r {
    
class TrackDrawable : public sf::Drawable {
    public:
        TrackDrawable();
        TrackDrawable(const TrackDrawable & _other);
        TrackDrawable(const Track & _track);
     
        TrackDrawable & operator = (const TrackDrawable & _other);
    
        void loadFromTrack(const Track & _track);
    
        // properties
        void setColor(const sf::Color & _value) { this->mColor = _value; this->mIsDirty = true; }
        const sf::Color & getColor() const { return this->mColor; }
    
        void setThickness(float _value) { this->mThickness = _value; this->mIsDirty = true; }
        float getThickness() const { return this->mThickness; }
    
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
    private:
        void updateVB() const;
        
    private:
        // One Track Segment
        struct Segment {
            unsigned int mPoint1;   // Index of the first Point
            unsigned int mPoint2;   // Index of the second Point
            
            Segment()
                : mPoint1(0), mPoint2(0) { }
            Segment(unsigned int _point1, unsigned int _point2)
                : mPoint1(_point1), mPoint2(_point2) { }
        };
    
        Track::Points                   mPoints;                // track points
        Track::Points                   mDirections;            // track directions
    
        std::vector<Segment>            mSegements;             // track segements
        sf::Color                       mColor;                 // track color
        float                           mThickness;             // track tickness (rendering only)
        
        bool                            mIsDirty;               // vertex buffer needs to be updated
        sf::VertexArray                 mVertices;              // vertex buffer
    
        // Debug Stuff
        std::vector<sf::CircleShape>    mTrackPoints;
        std::vector<sf::CircleShape>    mTrackDirPoints;
        std::vector<sf::CircleShape>    mTrackPivotPoints;
    
};

}

#endif /* defined(__Rac0r__Track__) */
