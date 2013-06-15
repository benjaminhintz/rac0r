//
//  Screen.h
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__Screen__
#define __Rac0r__Screen__

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

typedef std::shared_ptr<sf::Drawable> drawable_ptr;

class Screen : public sf::Drawable {
public:
    Screen(sf::VideoMode& videoMode) : videoMode(videoMode) {}
    
    void addElement(drawable_ptr element) {
        uiElemente.push_back(element);
    }
    
    virtual void layout(sf::Time elapsed) {};
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    virtual ~Screen() = default;

private:
    sf::VideoMode videoMode;
    std::vector<drawable_ptr> uiElemente;

};



#endif /* defined(__Rac0r__Screen__) */
