//
//  ButtonView.cpp
//  Rac0r
//
//  Created by Jannes on Jun/16/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "ButtonView.h"

#include <iostream>

ButtonView::ButtonView(const Rect& frame) :
    View(frame),
    backgroundNormal(10, 49, 97),
    backgroundActivated(0, 72, 255),
    textHighlighted(222, 204, 0),
    textActivated(236, 240, 127)
{
    // Set text font
    textLabel.setFont(ButtonView::getDefaultFont());
    
    applyStyle();
    layout();
}

const sf::Font& ButtonView::getDefaultFont() {
    static sf::Font defaultFont;
    static bool isLoaded = false;

    // TODO: put this in the header file as a static variable
	#ifdef __linux
	std::string fontDir = "fonts/";
	#endif
	#ifdef __APPLE__
	std::string fontDir = "";
	#endif
    
    if (!isLoaded) {
        if (!defaultFont.loadFromFile(resourcePath() + fontDir +  "Tahoma.ttf")) {
            // Error while loading the font
            std::cerr << "Couldn't load Tahoma.ttf" << std::endl;
            // TODO: crash
        }
        isLoaded = true;
    }
    
    return defaultFont;
}

void ButtonView::applyStyle() {
    // Background color
    background.setFillColor(backgroundNormal);
    
    // Text properties
    textLabel.setColor(sf::Color::White);
    textLabel.setStyle(sf::Text::Bold);
    
    // Apply further styles depending on the state
    switch (state) {
        case ViewState::normal:
            return;
            
        case ViewState::activated:
            background.setFillColor(backgroundActivated);
            textLabel.setColor(textActivated);
            return;
        case ViewState::highlighted:
            textLabel.setColor(textHighlighted);
            return;
    }
}

void ButtonView::layout() {
    // Set the background shape's color
    background.setSize(size);
    
    // Set the character size to be 40% of the height
    unsigned int textSize = static_cast<unsigned int>(0.4 * size.y);
    textLabel.setCharacterSize(textSize);
    
    // Center the text
    sf::FloatRect bounds = textLabel.getLocalBounds();
    sf::Vector2f position;
    position.x = static_cast<int>((size.x / 2) - (bounds.width / 2));
    position.y = static_cast<int>((size.y / 2) - 1.2 * (textSize / 2.0f));
    textLabel.setPosition(position);
}

void ButtonView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Apply transform from sf::Transformable
    states.transform *= getTransform();
    // Draw child elements
    target.draw(background, states);
    target.draw(textLabel, states);
}
