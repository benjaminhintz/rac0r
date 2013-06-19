//
//  View.cpp
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

#include "View.h"

#include <iostream>
#include "ResourcePath.hpp"

View::View(const Rect& frame) : frame(frame) {}

void View::setSize(float x, float y) {
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
    // Apply the transform from sf::Transformable
    states.transform *= getTransform();
    
    // Draw all child views
    for (sf::Drawable* view : childViews) {
        target.draw(*view, states);
    }
}

// Helper function that loads a default font
const sf::Font& View::getDefaultFont() {
    static sf::Font font;
    static bool isLoaded = false;
    if (!isLoaded) {
        if (!font.loadFromFile(resourcePath() + getFontPath() + "Tahoma.ttf")) {
            std::cerr << "Couldn't load the default font" << std::endl;
        }
        isLoaded = true;
    }
    return font;
}

const sf::Font& View::getSecondaryFont() {
    static sf::Font font;
    static bool isLoaded = false;
    if (!isLoaded) {
        if (!font.loadFromFile(resourcePath() + getFontPath() + "Russo_One.ttf")) {
            std::cerr << "Couldn't load the default font" << std::endl;
        }
        isLoaded = true;
    }
    return font;
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


