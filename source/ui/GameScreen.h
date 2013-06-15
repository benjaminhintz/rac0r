//
//  GameScreen.h
//  Rac0r
//
//  Created by Florian Kaluschke on 15.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__GameScreen__
#define __Rac0r__GameScreen__

#include <iostream>

#include "Screen.h"
#include "../track/TrackDrawable.h"
#include "../track/TrackLoader.h"
#include "../car/Car.h"

class GameScreen : public Screen {
private:
    std::string trackDir;
    // store tracks & track lines
    std::vector<Rac0r::Track> tracks;
    std::vector<Rac0r::TrackDrawable> trackDrawables;
    std::vector<Rac0r::Car> cars;
public:
    GameScreen(sf::VideoMode& videoMode);
    virtual void layout(sf::Time elapsed);
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual ~GameScreen() = default;
};

#endif /* defined(__Rac0r__GameScreen__) */
