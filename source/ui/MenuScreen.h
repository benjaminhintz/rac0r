//
//  MenuScreen.h
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__MenuScreen__
#define __Rac0r__MenuScreen__

#include "Screen.h"




class MenuScreen : public Screen {
public:
    MenuScreen(const Rect& frame);
    virtual ~MenuScreen() = default;
    virtual void handleEvent(sf::Event event);
    
protected:
    void setHighlight(int index);
    void setHighlightedToState(ViewState state);
    
private:
    bool highlighted = false;
    size_t highlightedItem = -1;
    void callFunction(int index, sf::Event event);
    void exit();
    
    //std::shared_ptr<ButtonView()> trackNumber;
    
    
};

#endif /* defined(__Rac0r__MenuScreen__) */
