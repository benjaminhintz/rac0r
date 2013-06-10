//
//  TrackLoader.cpp
//  Rac0r
//
//  Created by Jan Schulte on 03.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "TrackLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <math.h>

#include "../utils/vector2.h"



namespace Rac0r {
    
#define DEG_TO_RAD(x) (x) * (M_PI / 180.0f)
#define RAD_TO_DEG(x) (x) * (180.0f / M_PI)


TrackLoader::TrackLoader() :
    mCurveSteps(TrackLoader::DEFAULT_CURVE_STEPS) {
}

TrackLoader::~TrackLoader() {
}

    
std::vector<sf::Vector2f> TrackLoader::loadFromFile(const std::string & _fileName) {
    
    std::cout << _fileName << std::endl;
    
    // try to open the file
    std::ifstream file(_fileName, std::ifstream::in);
    if (!file.is_open()) {
        throw new std::runtime_error("Invalid file.");
    }
    
    std::vector<sf::Vector2f> result;

    // iterate over the file and read the data
    std::string line;
    while (getline(file, line)) {
        std::istringstream in(line);    // make stream for the line (easier to parse..)
        
        // read the track type
        std::string type;
        in >> type;
        
        // read in x, y, dirX, dirY
        float x, y, dirX, dirY;
        in >> x >> y >> dirX >> dirY; 

        // convert to sf types
        sf::Vector2f point(x, y);
        sf::Vector2f dir(dirX, dirY);
        
        // distinguish between track types
        if (type == "s") { // straight line
        
            result.push_back(point);
            
            std::cout << "Info: Straight track part found. Point(" << point << ")" << std::endl;
        } else if (type == "ll") { // left-left (90 deg)
            
            this->computeCurve(TrackLoader::Curve_Rotation::COUNTER_CLOCK_WISE, 90.0f, point, dir, result);
            
            std::cout << "Info: Left-Left 90 degree track part found. Point(" << point << ")" << std::endl;
        } else if (type == "l") { // left-left (90 deg)

            this->computeCurve(TrackLoader::Curve_Rotation::COUNTER_CLOCK_WISE, 45.0f, point, dir, result);
            
            std::cout << "Info: Left-Left 45 degree track part found. Point(" << point << ")" << std::endl;
        } else if (type == "rr") { // right-right (90 deg)

            this->computeCurve(TrackLoader::Curve_Rotation::CLOCK_WISE, 90.0f, point, dir, result);
            
            std::cout << "Info: Right-Right 90 degree track part found. Point(" << point << ")" << std::endl;
        } else if (type == "r") { // right-right (45 deg)
            
            this->computeCurve(TrackLoader::Curve_Rotation::CLOCK_WISE, 45.0f, point, dir, result);
            
            std::cout << "Info: Right-Right 45 degree track part found. Point(" << point << ")" << std::endl;
        } else if (type == "c") { // completed (start - finish are connected
            std::cout << "Info: track end found." << std::endl;
            break;
        } else { // TODO: Unimplemented
            std::cout << "Error: Unimplemented control command found. Command: " << type << std::endl;
        }
        
    }
    
    return result;
}

void TrackLoader::computeCurve(Curve_Rotation _roation, float _degree, const sf::Vector2f & _point, const sf::Vector2f & _dir, std::vector<sf::Vector2f> & _result) {
    
    // sanity check
    if (this->mCurveSteps == 0) {
        this->mCurveSteps = TrackLoader::DEFAULT_CURVE_STEPS;
    }
    
    bool cw = static_cast<bool>(_roation);
   
    // compute pivot
    float dirLen = length(_dir);
    sf::Vector2f normDir = normalize(_dir);
    sf::Vector2f orthDir = orthogonal(normDir);
    orthDir = orthDir * (dirLen * 1.5f); // abstand vom punkt zum mitelpunkt
    sf::Vector2f pivot = _point + (cw ? - orthDir : orthDir);

    // compute rotation steps
    float delta = (_degree / static_cast<float>(this->mCurveSteps));
    
    // compute radius
    float radius = abs(length(pivot - _point));
    
    // compute rotation start angle
    sf::Vector2f av(1.0f, 0.0f);
    //float startAngle = atan2(_dir.x, _dir.y) - DEG_TO_RAD(180.0f); // Orginal LL
    float startAngle = atan2(_dir.x, _dir.y) - (cw ? 0.0f : DEG_TO_RAD(180.0f));
    
    // sf::Vector2f rotPoint = normalize(_dir);
    sf::Vector2f rotPoint(1.0f, 0.0f);
    
    //std::cout << "Start Angle:" << startAngle << std::endl;
    //std::cout << "Start Dir:" << _dir << std::endl;
    //std::cout << "Start Angle:" << RAD_TO_DEG(startAngle) << std::endl;
    
    // generate curve
    for (unsigned int i = 0; i < this->mCurveSteps; ++i) {
        float angle = RAD_TO_DEG(startAngle) + (delta * static_cast<float>(i) * (cw ? -1.0f : 1.0f));
        //std::cout << "New Angle:" << angle << std::endl;
        
        float s = sin(DEG_TO_RAD(angle));
        float c = cos(DEG_TO_RAD(angle));
        //std::cout << "Sin: " << s  << " - Cos: " << c << std::endl;
   
        sf::Vector2f point(rotPoint.x * c + rotPoint.y * s, -rotPoint.x * s + rotPoint.y * c);
        //std::cout << "Rotated Point(" << i << "): " << point << std::endl;
        
        point *= radius;
        point += pivot;
    
        //std::cout << "Translated Point(" << i << "): " << point << std::endl;
        
        _result.push_back(point);
    }
 
}



}

