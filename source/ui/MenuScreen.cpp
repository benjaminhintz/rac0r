//
//  MenuScreen.cpp
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include "MenuScreen.h"

#include "ResourcePath.hpp"

using namespace std;

MenuScreen::MenuScreen(const Rect& frame) : Screen(frame) {
    vector<string> menuItems;
    menuItems.push_back("Play");
    menuItems.push_back("Choose track");
    menuItems.push_back("Exit");
    
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