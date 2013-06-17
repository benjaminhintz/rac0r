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
#include "../car/Car.h"


class GameScreen : public Screen, public Rac0r::CarEventListener {
public:
    GameScreen(const Rect& frame, int playerCount, std::string trackPath);
    constexpr static const int              START_INTERVAL                  =   1000;
    static const std::string                COUNTDOWN_STRINGS[4];
    
     // start line shape constants
    constexpr static const float            START_LINE_WIDTH                =   2.0f;
    
    // Game Logic constants
    constexpr static const int              MAX_LAPS                        =   1;
    
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
    void restart();
    void start();
    
private:
    
    class Player {
        public:
            size_t          mLapCount;
            size_t          mLapTime;
            size_t          mTotalTime;
            Rac0r::Car*     mCar;
        
            Player(Rac0r::Car * _car) : mLapCount(0), mLapTime(0), mTotalTime(0), mCar(_car) { }
        
            void reset() {
                mLapCount = 0;
                mLapTime = 0;
                mTotalTime = 0;
            }
        
            void accelerate() {
                if (mLapCount < MAX_LAPS) {
                    mCar->accelerate();
                }
            }
    };
    
	#ifdef __linux
	std::string trackDir = "tracks/";
	#endif
	#ifdef __APPLE__
	std::string trackDir = "";
	#endif
    
    // store tracks & track lines
    std::vector<Rac0r::Track>           tracks;
    std::vector<Rac0r::TrackDrawable>   trackDrawables;
    std::vector<Rac0r::Car*>            cars;
    sf::RectangleShape                  mStartLine;
    
    // ui elements
    sf::Text                            mCountdownTimerText;
    
    // game logic
    std::vector<Player>                 mPlayers;
    sf::Time                            mCountdownTimer;
    int                                 mStartCountdown;
    bool                                mGameRunning;
    
    sf::Time                            mGameTimer;
    
};

#endif /* defined(__Rac0r__GameScreen__) */
