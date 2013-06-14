//
//  main.cpp
//  Rac0r
//
//  Created by Jan Schulte on 02.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//
 


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.hpp"


#include "track/TrackDrawable.h"
#include "track/TrackLoader.h"
#include "ui/Screen.h"
#include "ui/MenuScreen.h"
#include "car/Car.h"

#include "utils/vector2.h"

// TODO: Den Shit hier muss nacher in den Game State in dem man das SPiel spielt
class GameState : public Rac0r::CarEventListener {
    virtual void onCarDriftedOffTrack(Rac0r::Car & _car) {
        std::cout << "Car drifted off track." << std::endl;
        //_car.resetToLastValidPosition();
    }
    
    virtual void onCarMovedThroughStart(Rac0r::Car & _car) {
        std::cout << "Car moved through start." << std::endl;
    }
    
    virtual void onCarStartedFromStart(Rac0r::Car & _car) {
        std::cout << "Car started from start." << std::endl;
    }

};


int main(int, char const** argv) {

    std::string trackDir;
    
    #ifdef __linux
	std::string tmp = argv[0];
	Global::__path = tmp.substr(0, tmp.find_last_of('/'));
    trackDir = "tracks/";
    #endif


    
    
	int numTracks = 1;

    // Setup Rendering Settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    
    // Create the main window
    sf::VideoMode videoMode(1024, 768);
    sf::RenderWindow window(videoMode, "Rac0r", sf::Style::Default, settings);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // store tracks & track lines
    std::vector<Rac0r::Track> tracks;
    std::vector<Rac0r::TrackDrawable> trackDrawables;
    std::vector<Rac0r::Car> cars;
    
    // Load Main Track
    Rac0r::TrackLoader trackLoader;
    Rac0r::Track mainTrack = trackLoader.loadFromFile(resourcePath() + trackDir + "test4.track");

    
    mainTrack.setCenter(sf::Vector2f(videoMode.width / 2, videoMode.height / 2));
    mainTrack.scaleToFitBounds(sf::Vector2f(videoMode.width, videoMode.height), false, -0.2f);
    
    tracks.push_back(mainTrack);
    
    // create sub tracks & their lines
    for (unsigned int i = 0; i < numTracks-1; ++i) {
        Rac0r::Track subTrack = mainTrack;
        subTrack.scaleToFitBounds(sf::Vector2f(videoMode.width, videoMode.height), true, -(20.0f * static_cast<float>(i+1)));
        tracks.push_back(subTrack);
    }
    
    // TEMP
    GameState gameState;
    
    // create track line renderer
    unsigned int color = 0;
    sf::Color colors[4] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
    for (auto & track : tracks) {
        Rac0r::TrackDrawable trackDrawable(track);
        trackDrawable.setThickness(2.0f);
        trackDrawable.setColor(colors[color]);
        trackDrawables.push_back(trackDrawable);
        
        // create cars for the track
        Rac0r::Car car(track, &gameState);
        car.setColor(colors[color++]);
        cars.push_back(car);
    }
    
    // delta time handling
    sf::Clock timer;
    
    // Start the game loop
    while (window.isOpen()) {
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Espace pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            //* TODO
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                cars[0].accelerate();
            }
            //*/
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                cars[0].resetToLastValidPosition();
            }
        }

        // Clear screen
        window.clear();

        // compute delta time
        sf::Time elapsed = timer.restart();
        
        // Vector mit abstrakten screens 
        std::vector<Screen*> screens;
        
        // Erster Screen
        MenuScreen ersterBildschirm;
        screens.push_back(&ersterBildschirm);
        
        // Bildschirm zeichnen
        window.draw(*screens.back());

        //screens.push_back(ersterBildschirm);
        
        // Render Tracks
        for (auto & trackDrawable : trackDrawables) {
            window.draw(trackDrawable);
        }
        
        // Render cars
        for (auto & car : cars) {
            car.update(elapsed);
            car.draw(window);
        }
        
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
