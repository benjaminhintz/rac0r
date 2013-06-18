//
//  GameScreen.cpp
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

#include "GameScreen.h"
#include "ResourcePath.hpp"
#include "../utils/vector2.h"
#include <iostream>


GameScreen::GameScreen(const Rect& frame, int playerCount, std::string trackPath) :
    Screen(frame),
    mGameRunning(false)
{
    createTracks(playerCount, trackPath);
    restart();
}

void GameScreen::createTracks(size_t _playerCount, const std::string & _trackFile) {

    // Load & Setup Main Track
    Rac0r::TrackLoader trackLoader;
    std::cout<< _trackFile<<std::endl;
    Rac0r::Track mainTrack = trackLoader.loadFromFile(_trackFile);
    
    float scaleOffset = 0.2;
    
    if (_playerCount % 2 == 0) {
        mainTrack.setCenter(sf::Vector2f(frame.width / 2, frame.height / 2));
        mainTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), false, -0.2);  // first initial scale
        mainTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), true, 8.0f);  // scale with directions
        mTracks.push_back(mainTrack);
    
        float offset = 0.0f;
        for (size_t i = 0; i < _playerCount-1; i++) {
            Rac0r::Track subTrack = mainTrack;
            offset += (scaleOffset * 20.0f * static_cast<float>(i+1)) * (i % 2 == 0 ? -1.0f : 1.0f);
            std::cout << "Offset: " << offset << std::endl;
            subTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), true, offset);
            mTracks.push_back(subTrack);
        }
        
    } else {
        mainTrack.setCenter(sf::Vector2f(frame.width / 2, frame.height / 2));
        mainTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), false, -0.2);
        mTracks.push_back(mainTrack);
    
        float offset = 0.0f;
        for (size_t i = 0; i < _playerCount-1; i++) {
            Rac0r::Track subTrack = mainTrack;
            offset += (scaleOffset * 20.0f * static_cast<float>(i+1)) * (i % 2 == 0 ? 1.0f : -1.0f);
            std::cout << "Offset: " << offset << std::endl;
            subTrack.scaleToFitBounds(sf::Vector2f(frame.width, frame.height), true, offset);
            mTracks.push_back(subTrack);
        } 
    }
    
    // create track line renderer
    unsigned int color = 0;
    for (auto & track : mTracks) {
        Rac0r::TrackDrawable trackDrawable(track);
        trackDrawable.setThickness(2.0f);
        trackDrawable.setColor(Rac0r::Constants::GAME_TRACK_COLOR[color++]);
        mTrackDrawables.push_back(trackDrawable);
    }
    
    // create start line
    float trackInnerOffset = 20.0f * scaleOffset;
    float height = trackInnerOffset * static_cast<float>(mTracks.size()-1) + trackInnerOffset * 2.0f;
    this->mStartLine = sf::RectangleShape(sf::Vector2f(GameScreen::START_LINE_WIDTH, height));
    this->mStartLine.setOrigin(GameScreen::START_LINE_WIDTH / 2.0f, 0.0f);
    sf::Vector2f startPos = mTracks[mTracks.size()-1][0];
    sf::Vector2f nextPos = mTracks[mTracks.size()-1][1];
    sf::Vector2f startPosDir = Rac0r::normalize(nextPos - startPos);
    sf::Vector2f startPosDirOrtho = Rac0r::orthogonal(startPosDir) * (height - trackInnerOffset);
    
    this->mStartLine.setPosition(startPos + startPosDirOrtho);
    this->mStartLine.setRotation(RAD_TO_DEG(Rac0r::heading(startPosDir)));
    this->mStartLine.setFillColor(sf::Color::White);
    
    createPlayer();
    
    // setup countdown text
    createCountdownTimer();
    updateCountdownTimer(Rac0r::Constants::COUNTDOWN_TIMER_STRINGS[0]);
}

void GameScreen::createPlayer() {
    // create cars & players
    unsigned int player = 0;
    for (auto & track : mTracks) {
        Rac0r::Car * car = new Rac0r::Car(track, this);
        car->setColor(Rac0r::Constants::GAME_TRACK_COLOR[player]);
        mPlayers.push_back(new Rac0r::Player(car, Rac0r::Constants::PLAYER_KEY[player++]));
    }
}

void GameScreen::restart() {
    this->mGameRunning = false;
    this->mStartCountdown = 0;
    
    sf::Clock timer;
    this->mCountdownTimer = timer.getElapsedTime();
    
    for (auto player : this->mPlayers) {
        player->reset();
    }
}

void GameScreen::start() {
    this->mGameRunning = true;
    this->mStartCountdown = 0;
    
    sf::Clock timer;
    this->mGameTimer = timer.getElapsedTime();

}

void GameScreen::createCountdownTimer() {
    mCountdownTimerFont.loadFromFile(resourcePath() + getFontPath() +  "Tahoma.ttf");

    this->mCountdownTimerText.setString(Rac0r::Constants::COUNTDOWN_TIMER_STRINGS[0]);
    this->mCountdownTimerText.setPosition(frame.width / 2, frame.height / 2);
    this->mCountdownTimerText.setFont(mCountdownTimerFont);
    this->mCountdownTimerText.setColor(sf::Color::White);
    this->mCountdownTimerText.setStyle(sf::Text::Bold);
}

void GameScreen::updateCountdownTimer(const std::string & _text) {
    this->mCountdownTimerText.setString(_text);
    
    unsigned int textSize = static_cast<unsigned int>(GameScreen::COUNTDOWN_FONT_SIZE * frame.width);
    this->mCountdownTimerText.setCharacterSize(textSize);

    sf::FloatRect bounds = this->mCountdownTimerText.getLocalBounds();
    sf::Vector2f position;
    position.x = static_cast<int>((frame.width / 2) - 1.1 * (bounds.width / 2));
    position.y = static_cast<int>((frame.height / 2) - 1.6 * (textSize / 2.0f));
    this->mCountdownTimerText.setPosition(position);
}

void GameScreen::layout(sf::Time elapsed) {
    static sf::Clock clock;
    
    sf::Time current = clock.getElapsedTime();
    
    // show countdown
    if (!this->mGameRunning) {
        sf::Int32 dt = current.asMilliseconds() - this->mCountdownTimer.asMilliseconds();
        if (dt > Rac0r::Constants::COUNTDOWN_TIMER_INTERVAL) {
            if (++this->mStartCountdown >= Rac0r::Constants::COUNTDOWN_TIMER_STRINGS_NUM) {
                start();
            } else {
                this->mCountdownTimer = clock.getElapsedTime();
                updateCountdownTimer(Rac0r::Constants::COUNTDOWN_TIMER_STRINGS[this->mStartCountdown]);
            }
        }
        
        return;
    }
    
    // update player
    for (auto player : this->mPlayers) {
        player->update(elapsed);
        
        //player.mLapTime = (current - this->mGameTimer).asMilliseconds();
        //std::cout << "Lap Time:"  << player.mLapTime << std::endl;
    }
    
    // TODO: REMOVE
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        for (auto player : this->mPlayers) {
            player->resetToLastValidPosition();
        }
    }
    
}

void GameScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    
    // Render Tracks
    for (auto & trackDrawable : mTrackDrawables) {
        trackDrawable.draw(target, states);
    }
    
    target.draw(this->mStartLine, states);
    
    if (!this->mGameRunning) {
        target.draw(this->mCountdownTimerText, states);
        return;
    }
    
    // draw players
    for (auto player : this->mPlayers) {
        player->draw(target, states);
    }
}


void GameScreen::onCarDriftedOffTrack(Rac0r::Car & _car) {
    std::cout << "Car drifted off track." << std::endl;
    //_car.resetToLastValidPosition();
}

void GameScreen::onCarMovedThroughStart(Rac0r::Car & _car) {

/*
    for (auto & player : this->mPlayers) {
        if (player.mCar == &_car) {
            player.mLapCount++;
            player.mLapTime = 0;
            player.mTotalTime = this->mGameTimer.asMilliseconds();
        }
    }
    */
    std::cout << "Car moved through start." << std::endl;
}

void GameScreen::onCarStartedFromStart(Rac0r::Car & _car) {
    std::cout << "Car started from start." << std::endl;
}
    

void GameScreen::handleEvent(sf::Event event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        // Escape pressed : exit
        quit = true;
    }
}

