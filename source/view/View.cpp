//
//  View.cpp
//  Rac0r
//
//  Created by Jannes on Jun/16/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "View.h"

#include <iostream>

View::View(const Rect& frame) :
    frame(frame),
    size(sf::Vector2f(frame.width, frame.height)),
    state(ViewState::normal)
{}

void View::setState(ViewState newState) {
    state = newState;
    applyStyle();
}

void View::setSize(float x, float y) {
    // TODO: also set the origin
    size = sf::Vector2f(x, y);
    frame = Rect(sf::Vector2f(0, 0), size);
    layout();
}

void View::addChild(view_ptr childView) {
    childViews.push_back(childView);
}

void View::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (view_ptr view : childViews) {
        target.draw(*view, states);
    }
}
