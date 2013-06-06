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
#define RAD_TO_DEF(x) (x) * (180.0f / M_PI)


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
    sf::Vector2f lastPoint;
    
    // iterate over the file and read the data
    std::string line;
    while (getline(file, line)) {
        std::istringstream in(line);    // make stream for the line (easier to parse..)
        
        // read the track type
        std::string type;
        in >> type;
        
        // distinguish between track types
        if (type == "s") { // straight line
            float x, y;
            in >> x >> y; // read in x and y
                        
            lastPoint = sf::Vector2f(x, y);
            result.push_back(lastPoint);
            
            std::cout << "Info: Straight track part found. Point(" << lastPoint << ")" << std::endl;
        } else if (type == "ll") { // left-left (90 deg)
            float x, y, dirX, dirY;
            in >> x >> y >> dirX >> dirY; // read in x and y
            
            sf::Vector2f point(x, y);
            sf::Vector2f dir(dirX, dirY);
            
            // compute inner radius
            float dirLen = length(dir);
            sf::Vector2f normDir = normalize(dir);
            sf::Vector2f orthDir = orthogonal(normDir);
            orthDir = orthDir * (dirLen * 1.5f); // abstand vom punkt zum mitelpunkt
            
            sf::Vector2f pivot = point + orthDir;
            
            std::cout << "Info: LL track part found. Point(" << point << ")" << std::endl;
            
            this->computeCurve(TrackLoader::Curve_Rotation::COUNTER_CLOCK_WISE, pivot, point, dir, result);
            
            std::cout << "Info: Left-Left 90 degree track part found. Point(" << point << ")" << std::endl;
        } else if (type == "rr") { // right-right (90 deg)
            /*
            float x, y, dirX, dirY;
            in >> x >> y >> dirX >> dirY; // read in x and y
            
            sf::Vector2f point(x, y);
            sf::Vector2f dir(dirX, dirY);
            TrackLoader::Curve_Origin origin = this->computeCurveOrigin(point, dir);
            sf::Vector2f pivot = this->computeCurvePivot(origin, point, dir);
            
            this->computeCurve(origin, TrackLoader::Curve_Rotation::COUNTER_CLOCK_WISE, pivot, point, result);
            */
            
           // std::cout << "Info: Right-Right 90 degree track part found. Point(" << point << ")" << std::endl;
        } else if (type == "c") { // completed (start - finish are connected
            std::cout << "Info: track end found." << std::endl;
            break;
        } else { // TODO: Unimplemented
            std::cout << "Error: Unimplemented control command found. Command: " << type << std::endl;
        }
        
    }
    
    return result;
}


void TrackLoader::computeCurve(Curve_Rotation _roation, const sf::Vector2f & _pivot, const sf::Vector2f & _point, const sf::Vector2f & _dir, std::vector<sf::Vector2f> & _result) {
    
    // sanity check
    if (this->mCurveSteps == 0) {
        this->mCurveSteps = TrackLoader::DEFAULT_CURVE_STEPS;
    }
    
    // store first point
    //_result.push_back(_point);
    
    // compute rotation steps
    float delta = (90.0f / static_cast<float>(this->mCurveSteps)) * static_cast<float>(_roation);
    
    // compute radius
    float radius = abs(length(_pivot - _point));
    
    // compute rotation start angle
    sf::Vector2f av(10.0f, 0.0f);
    float startAngle = acos(angle(av, _dir)) + DEG_TO_RAD(-270.0f);
    
    sf::Vector2f rotPoint = normalize(_dir);
    
    // generate curve
    for (unsigned int i = 0; i < this->mCurveSteps; ++i) {
    
        float s = sin(startAngle + DEG_TO_RAD(delta * static_cast<float>(i)));
        float c = cos(startAngle + DEG_TO_RAD(delta * static_cast<float>(i)));
        std::cout << "Sin: " << s  << " - Cos: " << c << std::endl;
        
        sf::Vector2f point(rotPoint.x * c - rotPoint.y * s,
                            rotPoint.x * s + rotPoint.y * c);
        point *= radius;
        
        point += _pivot;
       // point += _point;
        
        std::cout << "LL Translated Point(" << i << "): " << point << std::endl;
        
        _result.push_back(point);
    }
 
}



}

