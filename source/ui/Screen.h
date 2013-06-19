//
//  Screen.h
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

#ifndef __Rac0r__Screen__
#define __Rac0r__Screen__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "../view/View.h"

class Screen : public View {
public:
    Screen(const Rect& frame);
    virtual ~Screen() = default;
    
    virtual void handleEvent(sf::Event event) = 0;
    virtual void layout(sf::Time elapsed) {}
    
    // This value is read out from the main loop
    bool finished = false;
    bool quit = false;
};



#endif /* defined(__Rac0r__Screen__) */
