//
//  GameScreen.h
//  Rac0r
//
//  Created by Jannes Meyer on 15.06.13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__GameScreen__
#define __Rac0r__GameScreen__

#include <iostream>

#include "Screen.h"
#include "../track/TrackDrawable.h"
#include "../track/TrackLoader.h"
#include "../player/Player.h"


class GameScreen : public Screen, public Rac0r::CarEventListener {
public:
    
    // start line shape constants
    constexpr static const float            START_LINE_WIDTH                =   2.0f;
    
    // Countdown Timer constants
    constexpr static const float            COUNTDOWN_FONT_SIZE             =   0.2f;
    
    
public:
    GameScreen(const Rect& frame, int playerCount, std::string trackPath);
    virtual ~GameScreen() = default;
    
    virtual void handleEvent(sf::Event event);
    virtual void layout(sf::Time elapsed);
    
    virtual void onCarDriftedOffTrack(Rac0r::Car & _car);
    virtual void onCarMovedThroughStart(Rac0r::Car & _car);
    virtual void onCarStartedFromStart(Rac0r::Car & _car);
    
protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
private:
    void createTracks(size_t _playerCount, const std::string & _trackFile);
    void createPlayer();
    
    void restart();
    void start();
    
private:
    void createCountdownTimer();
    void updateCountdownTimer(const std::string & _text);
    
private:
    // track rendering
    std::vector<Rac0r::TrackDrawable>   mTrackDrawables;
    sf::RectangleShape                  mStartLine;
    
    // ui elements
    sf::Text                            mCountdownTimerText;
    sf::Font                            mCountdownTimerFont;
    
    // game logic
    std::vector<Rac0r::Track>           mTracks;
    std::vector<Rac0r::Player*>         mPlayers;
    sf::Time                            mCountdownTimer;
    int                                 mStartCountdown;
    bool                                mGameRunning;
    
    sf::Time                            mGameTimer;
    
};

#endif /* defined(__Rac0r__GameScreen__) */
