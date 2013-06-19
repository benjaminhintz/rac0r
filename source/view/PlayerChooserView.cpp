//
//  PlayerChooserView.cpp
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

#include "PlayerChooserView.h"

#include <iostream>
#include "ResourcePath.hpp"

PlayerChooserView::PlayerChooserView(std::string noun, int minValue, int maxValue, const Rect& frame) :
    View(frame),
    noun(noun),
    minValue(minValue),
    maxValue(maxValue),
    value(minValue)
{
    // Load textures
    arrowDownTexture.loadFromFile(resourcePath() + "arrowDown.png");
    arrowUpTexture.loadFromFile(resourcePath() + "arrowUp.png");

    // Initialize arrows
    arrowUp.setTexture(arrowUpTexture);
    arrowDown.setTexture(arrowDownTexture);
    addChild(arrowUp);
    addChild(arrowDown);
    
    // Initialize text
    textLabel.setFont(View::getDefaultFont());
    textLabel.setColor(sf::Color::White);
    textLabel.setStyle(sf::Text::Bold);
    addChild(textLabel);
    
    // Set the text
    setValue(value);
    // Trigger the initial layout (it will be triggered again whenever the size is changed)
    layoutChildviews();
}

int PlayerChooserView::getValue() {
    return value;
}

void PlayerChooserView::setValue(int newValue) {
    if (newValue >= minValue && newValue <= maxValue) {
        value = newValue;
        textLabel.setString(std::to_string(newValue) + " " + noun);
    }
}

void PlayerChooserView::handleEvent(sf::Event event) {
    bool pressed = (event.type == sf::Event::KeyPressed);
    bool released = (event.type == sf::Event::KeyReleased);
    
    if (pressed && event.key.code == sf::Keyboard::Down) {
        setValue(value - 1);
        layoutChildviews();
        arrowDown.move(0, 6);
    } else if (released && event.key.code == sf::Keyboard::Down) {
        layoutChildviews();
    }
    
    if (pressed && event.key.code == sf::Keyboard::Up) {
        setValue(value + 1);
        layoutChildviews();
        arrowUp.move(0, -6);
    } else if (released && event.key.code == sf::Keyboard::Up) {
        layoutChildviews();
    }
}

// This is called whenever the size is set
void PlayerChooserView::layoutChildviews() {
    sf::Vector2f position;
    sf::Vector2f size;

    // Set the character size to be 50% of the height
    unsigned int textSize = static_cast<unsigned int>(0.5 * frame.height);
    textLabel.setCharacterSize(textSize);
    // And center the text vertically
    position.x = 0;
    position.y = static_cast<unsigned int>(frame.height / 2 - 1.5 * (textSize / 2.0f));
    textLabel.setPosition(position);

    // Arrows
    size = sf::Vector2f(arrowUpTexture.getSize());
    position.x = frame.width - size.x;
    position.y = static_cast<int>(frame.height / 2 - size.y / 2);
    arrowUp.setPosition(position);
    
    size = sf::Vector2f(arrowDownTexture.getSize());
    position.x -= size.x - 8;
    arrowDown.setPosition(position);
}