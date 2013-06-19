//
//  MenuScreen.cpp
//  Rac0r
//
//  Created and copyright by
//  Benjamin Hintz
//  Florian Kaluschke
//  Jannes Meyer
//  David Leska
//  Lars Peterke
//  Jan Schulte
//  on Jun 2013. All rights reserved.
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
    description.setString(L"Drücke Enter, um das Spiel zu starten");
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
    
    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        // Escape pressed : exit
        quit = true;
    }

}

int MenuScreen::getPlayerCount() {
    return playerChooser.getValue();
}

