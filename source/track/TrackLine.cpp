//
//  TrackLine.cpp
//  Rac0r
//
//  Created by Jan Schulte on 02.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "TrackLine.h"
#include "../utils/vector2.h"

#include <GLUT/glut.h>


namespace Rac0r {
    
TrackLine::TrackLine() :
    mColor(sf::Color::White),
    mThickness(1.0f),
    mIsDirty(true) {
}

TrackLine::TrackLine(const TrackLine & _other) {
    this->operator=(_other);
}
    
TrackLine::~TrackLine() {
}

void TrackLine::loadFromTrack(const Track & _track) {
    
    // copy all TrackLine points
    this->mPoints = _track.getPoints();
    
    // create segments    
    for (size_t i = 0; i < this->mPoints.size(); ++i) {
        this->mSegements.push_back(Segment(i, (i+1 < this->mPoints.size()) ? i+1 : 0));
    }
    
    // update vertex buffer
    this->updateVB();
}

TrackLine & TrackLine::operator = (const TrackLine & _other) {

    if (this != &_other) {
		this->mPoints = _other.mPoints;
		this->mSegements = _other.mSegements;
		this->mColor = _other.mColor;
        this->mThickness = _other.mThickness;
        this->mIsDirty = true;
	}
    
	return *this;
}
    
void TrackLine::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    if (this->mIsDirty) {
        this->updateVB();
    }
    
    states.transform *= getTransform();
    
    target.draw(this->mVertices, states);
}
    
    
void TrackLine::updateVB() const {
    
    //this->mVertices.clear();
    
    // create vertex array
    sf::VertexArray * vb = const_cast<sf::VertexArray*>(&this->mVertices); // get rid of const...
    vb->setPrimitiveType(sf::Quads);
    vb->resize(this->mSegements.size() * 4);
    
    // create line constructed out of connected quads
    float halfThickness = this->mThickness * 0.5f;
    sf::Vector2f point1, point2;
    size_t i = 0;
    sf::Vertex * currentQuad = nullptr;
    sf::Vertex * lastQuad = nullptr;
    for (auto & segment : this->mSegements) {
        currentQuad = &(*vb)[i++ * 4];
    
        // get segement points
        point1 = this->mPoints[segment.mPoint1];
        point2 = this->mPoints[segment.mPoint2];
        
        // compute normalized direction
        sf::Vector2f dir = normalize(point2 - point1);
        
        // compute orthogonal vectors
        sf::Vector2f orth1 = sf::Vector2f(dir.y, -dir.x) * halfThickness;
        sf::Vector2f orth2 = sf::Vector2f(-dir.y, dir.x) * halfThickness;
        
        // compute quad edges    
        // build connection to last quad
        if (lastQuad != nullptr) {
            currentQuad[0].position = lastQuad[3].position;
            currentQuad[1].position = lastQuad[2].position;
        } else {
            currentQuad[0].position = point1 + orth2;
            currentQuad[1].position = point1 + orth1;
        }
        
        if (i < this->mSegements.size()) {
            currentQuad[2].position = point2 + orth1;
            currentQuad[3].position = point2 + orth2;
        } else {
            // connect to first
            sf::Vertex * firstQuad = &(*vb)[0];
            
            currentQuad[3].position = firstQuad[0].position;
            currentQuad[2].position = firstQuad[1].position;
        }
        
        /*
        std::cout << "Segment: " << i-1 << std::endl;
        std::cout << "[0] " << currentQuad[0].position << std::endl;
        std::cout << "[1] " << currentQuad[1].position << std::endl;
        std::cout << "[2] " << currentQuad[2].position << std::endl;
        std::cout << "[3] " << currentQuad[3].position << std::endl;
        */
        
        // set quad color
        currentQuad[0].color = this->mColor;
        currentQuad[1].color = this->mColor;
        currentQuad[2].color = this->mColor;
        currentQuad[3].color = this->mColor;
        
        // store last quad
        lastQuad = currentQuad;
    }

    // get rid of const and set the flag
    bool * dirty = const_cast<bool*>(&this->mIsDirty);
    *dirty = false;
}

    
} // namespace end
