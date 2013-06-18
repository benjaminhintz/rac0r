//
//  View.cpp
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

#include "View.h"

#include <iostream>
#include "ResourcePath.hpp"

View::View(const Rect& frame) :
    frame(frame),
    state(ViewState::normal)
{}

void View::setState(ViewState newState) {
    state = newState;
    applyStyle();
}

void View::setSize(float x, float y) {
    // TODO: What about the origin?
    frame = Rect(sf::Vector2f(0, 0), sf::Vector2f(x, y));
    layoutChildviews();
}

sf::Vector2f View::getSize() {
    return sf::Vector2f(frame.width, frame.height);
}

void View::addChild(sf::Drawable& child) {
    childViews.push_back(&child);
}

void View::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply transform from sf::Transformable
    states.transform *= getTransform();
    
    // Draw all child views
    for (sf::Drawable* view : childViews) {
        target.draw(*view, states);
    }
}

// Helper function that loads a default font
const sf::Font& View::getDefaultFont() {
    static sf::Font defaultFont;
    static bool isLoaded = false;
    
    if (!isLoaded) {
        if (!defaultFont.loadFromFile(resourcePath() + getFontPath() + "Tahoma.ttf")) {
            std::cerr << "Couldn't load Tahoma.ttf" << std::endl;
            // TODO: crash
        }
        isLoaded = true;
    }
    
    return defaultFont;
}

const std::string & View::getFontPath() {

    #ifdef __linux
	static std::string fontDir = "fonts/";
	#elif __APPLE__
	static std::string fontDir = "";
    #else
    static std::string fontDir = "";
	#endif

    return fontDir;
}


