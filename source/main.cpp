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

#include "track/TrackLine.h"
#include "track/TrackLoader.h"


int main(int, char const**) {
    
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
    std::vector<Rac0r::TrackLine> trackLines;
    
    // Load Main Track
    Rac0r::TrackLoader trackLoader;
    Rac0r::Track mainTrack = trackLoader.loadFromFile(resourcePath() + "test4.track");
    
    mainTrack.setCenter(sf::Vector2f(videoMode.width / 2, videoMode.height / 2));
    mainTrack.scaleToFitBounds(sf::Vector2f(videoMode.width, videoMode.height), false, -0.2f);
    
    tracks.push_back(mainTrack);
    
    // create sub tracks & their lines
    for (unsigned int i = 0; i < 4; ++i) {
        Rac0r::Track subTrack = mainTrack;
        subTrack.scaleToFitBounds(sf::Vector2f(videoMode.width, videoMode.height), true, (20.0f * static_cast<float>(i+1)));
        tracks.push_back(subTrack);
    }
    
    // create track line renderer
    unsigned int color = 0;
    sf::Color colors[4] = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
    for (auto & track : tracks) {
        Rac0r::TrackLine trackLine(track);
        trackLine.setThickness(4.0f);
        trackLine.setColor(colors[color++]);
        trackLines.push_back(trackLine);
    }
    
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
        }

        // Clear screen
        window.clear();

        // TODO: Render Scene
        for (auto & trackLine : trackLines) {
            window.draw(trackLine);
        }
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
