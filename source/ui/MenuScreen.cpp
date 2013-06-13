//
//  MenuScreen.cpp
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "MenuScreen.h"
#include "ResourcePath.hpp"

MenuScreen::MenuScreen() {
    if (!font.loadFromFile(resourcePath() + "Tahoma.ttf")) {
        // Fehler beim Laden
    }
    
    text.setFont(font);
    text.setPosition(100, 100);
    text.setString("Hello world");
    text.setCharacterSize(24); // in pixels, not points!
    text.setColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
}

void MenuScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Draw text
    target.draw(text);
}