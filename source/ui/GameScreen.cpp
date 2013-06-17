//
//  GameScreen.cpp
//  Rac0r
//
//  Created by Jannes Meyer on 15.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "GameScreen.h"

#include "ResourcePath.hpp"

GameScreen::GameScreen(const Rect& frame) :
    Screen(frame),
    mGameRunning(false)
{
    createTracks(5, "test5.track");
    restart();
}

void GameScreen::createTracks(size_t _playerCount, const std::string & _trackFile) {

    // Load & Setup Main Track
    Rac0r::TrackLoader trackLoader;
    Rac0r::Track mainTrack = trackLoader.loadFromFile(resourcePath() + trackDir + _trackFile);
    
    float scaleOffset = 0.2;
    
    if (_playerCount % 2 == 0) {
        mainTrack.setCenter(sf::Vector2f(frame.width / 2, frame.height / 2));
        mainTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), false, -0.2);  // first initial scale
        mainTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), true, 8.0f);  // scale with directions
        tracks.push_back(mainTrack);
    
        float offset = 0.0f;
        for (size_t i = 0; i < _playerCount-1; i++) {
            Rac0r::Track subTrack = mainTrack;
            offset += (scaleOffset * 20.0f * static_cast<float>(i+1)) * (i % 2 == 0 ? -1.0f : 1.0f);
            
            subTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), true, offset);
            tracks.push_back(subTrack);
        }
        
    } else {
        mainTrack.setCenter(sf::Vector2f(frame.width / 2, frame.height / 2));
        mainTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), false, -0.2);
        tracks.push_back(mainTrack);
    
        float offset = 0.0f;
        for (size_t i = 0; i < _playerCount-1; i++) {
            Rac0r::Track subTrack = mainTrack;
            offset += (scaleOffset * 20.0f * static_cast<float>(i+1)) * (i % 2 == 0 ? 1.0f : -1.0f);
            
            subTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), true, offset);
            tracks.push_back(subTrack);
        } 
    }
    
    // create track line renderer
    unsigned int color = 0;
    sf::Color colors[5] = {
		sf::Color(0,153,205,153),
		sf::Color(102, 153, 0, 153),
		sf::Color(153, 51, 204, 153),
		sf::Color(255, 136, 0, 153),
		sf::Color(204, 0, 0, 153)
    };
    for (auto & track : tracks) {
        Rac0r::TrackDrawable trackDrawable(track);
        trackDrawable.setThickness(2.0f);
        trackDrawable.setColor(colors[color]);
        trackDrawables.push_back(trackDrawable);
        
        // create cars for the track
        Rac0r::Car car(track, this);
        car.setColor(colors[color++]);
        cars.push_back(car);
    }
}

void GameScreen::restart() {
    this->mGameRunning = false;
    
    sf::Clock timer;
    this->mStartTimer = timer.getElapsedTime();
}

void GameScreen::layout(sf::Time elapsed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
    	if(cars.size() >= 1) cars[0].accelerate();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
    	if(cars.size() >= 2) cars[1].accelerate();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
    	if(cars.size() >= 3) cars[2].accelerate();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
    	if(cars.size() >= 4) cars[3].accelerate();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
    	if(cars.size() >= 5) cars[4].accelerate();
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        cars[0].resetToLastValidPosition();
        cars[1].resetToLastValidPosition();
        cars[2].resetToLastValidPosition();
        cars[3].resetToLastValidPosition();
        cars[4].resetToLastValidPosition();
    }
    
    for (auto & car : cars) {
        car.update(elapsed);
    }
}

void GameScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Render Tracks
    for (auto & trackDrawable : trackDrawables) {
        trackDrawable.draw(target, states);
    }
    
    // Render cars
    for (auto & car : cars) {
        car.draw(target, states);
    }
}


void GameScreen::onCarDriftedOffTrack(Rac0r::Car & _car) {
    std::cout << "Car drifted off track." << std::endl;
    //_car.resetToLastValidPosition();
}

void GameScreen::onCarMovedThroughStart(Rac0r::Car & _car) {
    std::cout << "Car moved through start." << std::endl;
}

void GameScreen::onCarStartedFromStart(Rac0r::Car & _car) {
    std::cout << "Car started from start." << std::endl;
}
    

void GameScreen::handleEvent(sf::Event event) {
	// TODO: implement
}

