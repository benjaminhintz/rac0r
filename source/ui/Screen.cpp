//
//  Screen.cpp
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "Screen.h"

#include <iostream>

Screen::Screen(const Rect& frame) : View(frame) {}

void Screen::setHighlight(int index) {
    if (index >=0 && index < childViews.size()) {
        // Remove the old highlight
        if (focus) {
            childViews[highlightedItem]->setState(ViewState::normal);
        }
        // Apply the new highlight
        focus = true;
        highlightedItem = index;
        childViews[highlightedItem]->setState(ViewState::highlighted);
    }
}

void Screen::setHighlightedToState(ViewState state) {
    if (focus) {
        childViews[highlightedItem]->setState(state);
    }
}

//void Screen::setHighlight(view_ptr view) {
//    // Find the new highlight
//    auto i = std::find(childViews.begin(), childViews.end(), view);
//    if (i != childViews.end()) {
//        (*i)->setState(ViewState::highlighted);
//    }
//}

void Screen::handleEvent(sf::Event event) {
    bool down = (event.type == sf::Event::KeyPressed);
    bool up = (event.type == sf::Event::KeyReleased);
    
    if (down && event.key.code == sf::Keyboard::Down) {
        if (!focus) {
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
    }
}