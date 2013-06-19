//
//  TrackDrawable.cpp
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

#include "TrackDrawable.h"
#include "../utils/vector2.h"

#ifdef __linux
#include <GL/glut.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif


namespace Rac0r {
    
TrackDrawable::TrackDrawable() :
    mColor(sf::Color::White),
    mThickness(3.0f),
    mIsDirty(true) {
}

TrackDrawable::TrackDrawable(const TrackDrawable & _other) {
    this->operator=(_other);
}

TrackDrawable::TrackDrawable(const Track & _track) : TrackDrawable() {
    this->loadFromTrack(_track);
}

void TrackDrawable::loadFromTrack(const Track & _track) {
    
    // copy all TrackDrawable points
    this->mPoints = _track.getPoints();
    
    // create segments    
    for (size_t i = 0; i < this->mPoints.size(); ++i) {
        this->mSegements.push_back(Segment(i, (i+1 < this->mPoints.size()) ? i+1 : 0));
    }
    
    // update vertex buffer
    this->updateVB();
}

TrackDrawable & TrackDrawable::operator = (const TrackDrawable & _other) {

    if (this != &_other) {
		this->mPoints = _other.mPoints;
        this->mDirections = _other.mDirections;
		this->mSegements = _other.mSegements;
		this->mColor = _other.mColor;
        this->mThickness = _other.mThickness;
        this->mIsDirty = true;
	}
    
	return *this;
}

    
void TrackDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    if (this->mIsDirty) {
        this->updateVB();
    }

    //states.transform *= getTransform();

    target.draw(this->mVertices, states);
    
    // DEBUG
    /*
    for (auto & point : this->mTrackPoints) {
        target.draw(point, states);
    }
    */
    /*
    for (auto & point : this->mTrackDirPoints) {
        target.draw(point, states);
    }
    */
}
    
    
void TrackDrawable::updateVB() const {
    
    // Debug Stuff
    std::vector<sf::CircleShape> * trackPoints = const_cast<std::vector<sf::CircleShape>*>(&this->mTrackPoints);
    trackPoints->clear();
    
    std::vector<sf::CircleShape> * trackDirPoints = const_cast<std::vector<sf::CircleShape>*>(&this->mTrackDirPoints);
    trackDirPoints->clear();
    
    // create vertex array
    sf::VertexArray * vb = const_cast<sf::VertexArray*>(&this->mVertices); // get rid of const...
    vb->setPrimitiveType(sf::Quads);
    vb->resize(this->mSegements.size() * 4);
    
    // create line constructed out of connected quads
    float halfThickness = this->mThickness * 0.5f;
    sf::Vector2f point1, point2;
    size_t i = 0;
    sf::Vertex * currentQuad = NULL;
    sf::Vertex * lastQuad = NULL;
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
        if (lastQuad != NULL) {
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
        
        // set quad color
        currentQuad[0].color = this->mColor;
        currentQuad[1].color = this->mColor;
        currentQuad[2].color = this->mColor;
        currentQuad[3].color = this->mColor;
        
        // store last quad
        lastQuad = currentQuad;
        
        // Debug Stuff
        sf::CircleShape debugPoint(2);
        debugPoint.setPosition(point1);
        debugPoint.setOrigin(1, 1);
        debugPoint.setFillColor(sf::Color::White);
        trackPoints->push_back(debugPoint);
        
        // compute point othogonal
        sf::Vector2f orthDir = orthogonal(normalize(point1 - point2)) * 8.0f;
        sf::CircleShape debugDirPoint(2);
        debugDirPoint.setPosition(point1 + orthDir);
        debugDirPoint.setOrigin(1, 1);
        debugDirPoint.setFillColor(sf::Color::Green);
        trackDirPoints->push_back(debugDirPoint);
    }

    // get rid of const and set the flag
    bool * dirty = const_cast<bool*>(&this->mIsDirty);
    *dirty = false;
}

    
} // namespace end
