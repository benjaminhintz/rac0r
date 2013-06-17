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
//    trackDir = "tracks/";
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
    
    // List of currently active screens
    // TODO: in ScreenManager packen, der Animationen kann
    std::vector<std::shared_ptr<Screen>> screens;
    Rect screenFrame(0, 0, videoMode.width, videoMode.height);
    screens.emplace_back(new MenuScreen(screenFrame));
    //screens.emplace_back(new GameScreen(screenFrame));
    // TODO: ScreenManager fragen
    auto currentScreen = screens.back();
    
    // delta time handling
    sf::Clock timer;
    
    // Start the game loop
    while (window.isOpen()) {
        
        // compute delta time
        sf::Time elapsed = timer.restart();

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close window : exit
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                // Escape pressed : exit
                window.close();
            } else {
                currentScreen->handleEvent(event);
            }
        }
        
        if(currentScreen->exit) {
            window.close();
        }
        
        // Update the screen's contents and tell it how much time passed since the last frame
        currentScreen->layout(elapsed);
        
        // Clear screen
        window.clear();

        // Draw
        window.draw(*currentScreen);
        
        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
