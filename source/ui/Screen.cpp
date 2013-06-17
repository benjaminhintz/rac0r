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


//void Screen::setHighlight(view_ptr view) {
//    // Find the new highlight
//    auto i = std::find(childViews.begin(), childViews.end(), view);
//    if (i != childViews.end()) {
//        (*i)->setState(ViewState::highlighted);
//    }
//}

