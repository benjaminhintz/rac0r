//
//  MenuScreen.cpp
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "MenuScreen.h"
#include "ResourcePath.hpp"

using namespace std;

MenuScreen::MenuScreen(const Rect& frame) :
    Screen(frame),
    playerChooser("Spieler", 1, 5),
    trackChooser()
{
    
    // Load textures
    if (!logoTexture.loadFromFile(resourcePath() + "logo.png")) {
        cerr << "Error while loading image" << endl;
    }
    
    // Logo
    logo.setTexture(logoTexture);
    addChild(logo);
    
    // Track image
    addChild(trackChooser);
    
    // Player chooser
    playerChooser.setSize(225, 48);
    addChild(playerChooser);

    // Description text
    description.setString("Druecke Enter, um das Spiel zu starten");
    description.setCharacterSize(28);
    description.setStyle(sf::Text::Bold);
    description.setColor(sf::Color::White);
    description.setFont(View::getDefaultFont());
    addChild(description);
    
    // Do the initial layout
    layoutChildviews();
}


// This function should be called initially and everytime the size of the window changes
void MenuScreen::layoutChildviews() {
    sf::Vector2f size;
    sf::Vector2f position;
    
    // Logo
    size = sf::Vector2f(logoTexture.getSize());
    position.x = static_cast<int>(frame.width / 2 - size.x / 2);
    position.y = 10;
    logo.setPosition(position);
    
    // Track
//    size = track.getSize();
//    position.x = static_cast<int>(frame.width / 2 - size.x / 2);
//    position.y = 350;
//    track.setPosition(position);
    
    
    // Player chooser
    size = playerChooser.getSize();
    position.x = static_cast<int>(frame.width / 2 - size.x / 2);
    position.y = 675;
    playerChooser.setPosition(position);
    
    // Track chooser
    size = trackChooser.getSize();
    position.x = static_cast<int>(frame.width / 2 - size.x / 2);
    position.y = 275;
    trackChooser.setPosition(position);
    
    // Description text
    sf::FloatRect bounds = description.getGlobalBounds();
    position.x = static_cast<int>(frame.width / 2 - bounds.width / 2);
    position.y = 720;
    description.setPosition(position);
    
    

}


void MenuScreen::handleEvent(sf::Event event) {
    bool pressed = (event.type == sf::Event::KeyPressed);
    
    playerChooser.handleEvent(event);
    trackChooser.handleEvent(event);
    
    
    if (pressed && event.key.code == sf::Keyboard::Return) {
        
        trackPath = trackChooser.getTrackPath();
        finished = true;
    
    }
    
//        if (pressed && event.key.code == sf::Keyboard::Return) {
//        trackPath = tracks.at(trackNumber).getTrackFile();
//        finished = true;
//    }
}

int MenuScreen::getPlayerCount() {
    return playerChooser.getValue();
}

