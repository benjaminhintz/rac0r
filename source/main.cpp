//
//  main.cpp
//  Rac0r
//
//  Created and copyright by
//  Benjamin Hintz
//  Florian Kaluschke
//  David Leska
//  Lars Peterke
//  Jan Schulte
//  on Jun 2013. All rights reserved.
//
 


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

#include "ResourcePath.hpp"
#include "ui/Screen.h"
#include "ui/MenuScreen.h"
#include "ui/GameScreen.h"

#include "utils/vector2.h"
#include "track/TrackFileManager.h"
#include "SoundMgr.h"

int main(int, char const** argv) {
    
    #ifdef __linux
	std::string tmp = argv[0];
	Global::__path = tmp.substr(0, tmp.find_last_of('/'));
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
    std::vector<std::shared_ptr<Screen>> screens;
    Rect screenFrame(0, 0, videoMode.width, videoMode.height);
    
    // Add the menu as the first screen
    std::shared_ptr<MenuScreen> menuScreen = std::make_shared<MenuScreen>(screenFrame);
    screens.push_back(menuScreen);
    auto currentScreen = screens.back();
    
    // delta time handling
    sf::Clock timer;
    
    //background music
    Rac0r::SoundMgr sMgr;
    
    //play music
    sMgr.play(0);
    
    // Start the game loop
    while (window.isOpen()) {
        // Compute delta time
        sf::Time elapsed = timer.restart();

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // Close window : exit
                window.close();
            } else {
                //pass the event to the current screen
                currentScreen->handleEvent(event);
            }
        }
        
        if(currentScreen->quit) {
            //check if there are more than one screen
            //if not pop back the currentscreen
            //if yes close the window
            if (screens.size()==1) {
                window.close();
            } else {
                screens.pop_back();
                currentScreen=screens.back();
            }
        }
        
        // The screen indicates that it is done with what it does
        if(menuScreen->finished) {
            auto gameScreen = std::make_shared<GameScreen>(screenFrame, menuScreen->getPlayerCount(), menuScreen->trackPath);
            screens.push_back(gameScreen);
            currentScreen = screens.back();
            
            // Avoid this being called again
            menuScreen->finished = false;
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
    
    //stop music
    sMgr.stop(0);
    
    //return the success state
    return EXIT_SUCCESS;
}
