//
//  MenuScreen.h
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__MenuScreen__
#define __Rac0r__MenuScreen__

#include <iostream>
#include "Screen.h"

class MenuScreen : public Screen {
public:
    MenuScreen(sf::VideoMode& videoMode);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual ~MenuScreen() = default;
    
private:
    sf::Text text;
    sf::Font font;
};

#endif /* defined(__Rac0r__MenuScreen__) */
