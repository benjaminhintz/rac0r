//
//  MenuScreen.cpp
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include <iostream>

#include "MenuScreen.h"

#include "ResourcePath.hpp"

using namespace std;

MenuScreen::MenuScreen(const Rect& frame) : Screen(frame) {
    vector<string> menuItems;
    menuItems.push_back("play");
    menuItems.push_back("choose track");
    menuItems.push_back("choose player");
    menuItems.push_back("exit");
    
    int i = 0;
    for (string menuItem : menuItems) {
        auto button = std::make_shared<ButtonView>();
        
        button->setText(menuItem);
        button->setPosition(50, 150 + 75 * i++);
        button->setSize(200, 50);
        button->setRotation(-15);
        
        addChild(button);
    }
    
    setHighlight(0);
}

void MenuScreen::setHighlight(int index) {
    if (index >=0 && index < childViews.size()) {
        // Remove the old highlight
        if (highlighted) {
            childViews[highlightedItem]->setState(ViewState::normal);
        }
        // Apply the new highlight
        highlighted = true;
        highlightedItem = index;
        childViews[highlightedItem]->setState(ViewState::highlighted);
    }
}

void MenuScreen::setHighlightedToState(ViewState state) {
    if (highlighted) {
        childViews[highlightedItem]->setState(state);
    }
}

void MenuScreen::handleEvent(sf::Event event) {
    bool down = (event.type == sf::Event::KeyPressed);
    bool up = (event.type == sf::Event::KeyReleased);
    
    if (down && event.key.code == sf::Keyboard::Down) {
        if (!highlighted) {
            setHighlight(0);
        } else {
            setHighlight(highlightedItem + 1);
        }
    } else if (down && event.key.code == sf::Keyboard::Up) {
        setHighlight(highlightedItem - 1);
    }
    if (down && event.key.code == sf::Keyboard::Return) {
        setHighlightedToState(ViewState::activated);
    }
    if (up && event.key.code == sf::Keyboard::Return) {
        setHighlightedToState(ViewState::highlighted);
        callFunction(highlightedItem, event);
    }
    if (up && event.key.code == sf::Keyboard::Left) {
        callFunction(highlightedItem, event);
    }
    if (up && event.key.code == sf::Keyboard::Right) {
        callFunction(highlightedItem, event);
    }
}

void MenuScreen::callFunction(int index, sf::Event event) {
    switch (index) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            if(event.key.code == sf::Keyboard::Left) {
                cout << "links" << endl;
            } else if(event.key.code == sf::Keyboard::Right) {
                cout << "rechts" << endl;
            }
            break;
        case 3:
            exit();
            break;
        default:
            break;
    }
}

void MenuScreen::exit() {
    Screen::exit = true;
}
