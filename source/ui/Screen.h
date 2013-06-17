//
//  Screen.h
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
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
    
    virtual void handleEvent(sf::Event event);
    virtual void layout(sf::Time elapsed) {}

protected:
    void setHighlight(int index);
    void setHighlightedToState(ViewState state);
    
private:
    bool focus = false;
    size_t highlightedItem = -1;
};



#endif /* defined(__Rac0r__Screen__) */
