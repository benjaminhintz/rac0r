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
#include "../track/TrackFileManager.h"
#include "../view/PlayerChooserView.h"

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
    int trackNumber = 0;
    std::vector<Rac0r::TrackFile> tracks;

    // Resources
    sf::Texture logoTexture;
    sf::Texture trackTexture;

    // Drawables
    sf::Sprite logo;
    sf::Sprite track;
    PlayerChooserView playerChooser;
    sf::Text description;
};

#endif /* defined(__Rac0r__MenuScreen__) */
