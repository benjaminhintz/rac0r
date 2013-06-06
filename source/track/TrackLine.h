//
//  Track.h
//  Rac0r
//
//  Created by Jan Schulte on 02.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__Track__
#define __Rac0r__Track__

#include <iostream>
#include <vector>
#include <stdexcept>

#include <SFML/Graphics.hpp>

namespace Rac0r {
    
class TrackLine : public sf::Drawable, public sf::Transformable {
    public:
        TrackLine();
        TrackLine(const TrackLine & _other);
        ~TrackLine();
    
        TrackLine & operator = (const TrackLine & _other);
    
        void loadFrom(const std::vector<sf::Vector2f> & _points);
    
    
        // properties
        void setColor(const sf::Color & _color) { this->mColor = _color; this->mIsDirty = true; }
        const sf::Color & getColor() const { return this->mColor; }
    
        void setThickness(float _thickness) { this->mThickness = _thickness; this->mIsDirty = true; }
        float getThickness() const { return this->mThickness; }
    
    protected:
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
    
        std::vector<sf::Vector2f>   mPoints;                // track points
        std::vector<Segment>        mSegements;             // track segements
        sf::Color                   mColor;                 // track color
        float                       mThickness;             // track tickness (rendering only)
        
        bool                        mIsDirty;               // vertex buffer needs to be updated
        sf::VertexArray             mVertices;              // vertex buffer
};

}

#endif /* defined(__Rac0r__Track__) */
