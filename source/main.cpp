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
    sf::RenderWindow window(sf::VideoMode(800, 600), "Rac0r", sf::Style::Default, settings);

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // TEST: Load Test Track
    Rac0r::TrackLoader trackLoader;
    std::vector<sf::Vector2f> trackPoints = trackLoader.loadFromFile(resourcePath() + "test4.track");
    
    Rac0r::TrackLine testTrack;
    testTrack.setThickness(4.0f);
    testTrack.setColor(sf::Color::Red);
    testTrack.loadFrom(trackPoints);
    testTrack.setPosition(50.0f, 50.0f);
    //testTrack.setScale(2.0f, 2.0f);
    
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
        window.draw(testTrack);
        
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
