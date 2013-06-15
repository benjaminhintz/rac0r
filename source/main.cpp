//
//  main.cpp
//  Rac0r
//
//  Created by Jan Schulte on 02.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//
 


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

#include "ResourcePath.hpp"
#include "ui/Screen.h"
#include "ui/MenuScreen.h"
#include "ui/GameScreen.h"

#include "utils/vector2.h"


int main(int, char const** argv) {
    
    #ifdef __linux
	std::string tmp = argv[0];
	Global::__path = tmp.substr(0, tmp.find_last_of('/'));
    trackDir = "tracks/";
    #endif

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

    // delta time handling
    sf::Clock timer;
    
    // Vector mit abstrakten screens
    std::vector<std::shared_ptr<Screen>> screens;
    // Erster Screen
    screens.emplace_back(new MenuScreen(videoMode));
    screens.emplace_back(new GameScreen(videoMode));
    
    // Start the game loop
    while (window.isOpen()) {
        
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
//            // Close window : exit
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            // Espace pressed : exit
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
//                window.close();
//            }
//            
//            //* TODO
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//                cars[0].accelerate();
//            }
//            //*/
//            
//            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
//                cars[0].resetToLastValidPosition();
//            }
        }

        // Clear screen
        window.clear();

        // compute delta time
        sf::Time elapsed = timer.restart();
        
        // Bildschirm zeichnen
        auto currentScreen = screens.back();
        currentScreen->layout(elapsed);
        window.draw(*currentScreen);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
