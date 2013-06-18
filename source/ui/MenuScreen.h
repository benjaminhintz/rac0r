//
//  MenuScreen.h
//  Rac0r
//
//  Created and copyright by
//  Benjamin Hintz
//  Florian Kaluschke
//  David Leska
//  Lars Peterke
//  Jan Schulte
//  on Jun 2013. All rights reserved.
//

#ifndef __Rac0r__MenuScreen__
#define __Rac0r__MenuScreen__

#include "Screen.h"
#include "../track/TrackFileManager.h"
#include "../view/PlayerChooserView.h"
#include "../view/TrackChooserView.h"

class MenuScreen : public Screen {
public:
    MenuScreen(const Rect& frame);
    virtual ~MenuScreen() = default;
    
    virtual void layoutChildviews();
    virtual void handleEvent(sf::Event event);
    
    // These values are read out from the main loop, so they have to be public
    int getPlayerCount();
    std::string trackPath;
    
private:

    // Resources
    sf::Texture logoTexture;
    sf::Texture trackTexture;

    // Drawables
    sf::Sprite logo;
    PlayerChooserView playerChooser;
    TrackChooserView trackChooser;
    sf::Text description;
};

#endif /* defined(__Rac0r__MenuScreen__) */