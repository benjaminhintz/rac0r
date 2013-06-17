//
//  GameScreen.cpp
//  Rac0r
//
//  Created by Jannes Meyer on 15.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "GameScreen.h"

#include "ResourcePath.hpp"

GameScreen::GameScreen(const Rect& frame) : Screen(frame) {
    int numTracks = 4;
    
    // Load Main Track
    Rac0r::TrackLoader trackLoader;
    Rac0r::Track mainTrack = trackLoader.loadFromFile(resourcePath() + trackDir + "test3.track");
    
    mainTrack.setCenter(sf::Vector2f(frame.width / 2, frame.height / 2));
    mainTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), false, -0.2f);
    
    tracks.push_back(mainTrack);
    
    // create sub tracks & their lines
    for (unsigned int i = 0; i < numTracks-1; ++i) {
        Rac0r::Track subTrack = mainTrack;
        subTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), true, -(20.0f * static_cast<float>(i+1)));
        tracks.push_back(subTrack);
    }
    
    // create track line renderer
    unsigned int color = 0;
    sf::Color colors[4] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
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

void GameScreen::layout(sf::Time elapsed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        cars[0].accelerate();
        cars[1].accelerate();
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        cars[0].resetToLastValidPosition();
        cars[1].resetToLastValidPosition();
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


