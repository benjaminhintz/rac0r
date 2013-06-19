//
//  GameScreen.cpp
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

#include "GameScreen.h"
#include "ResourcePath.hpp"
#include "../utils/vector2.h"

sf::Clock GameScreen::mClock = sf::Clock();

GameScreen::GameScreen(const Rect& frame, int playerCount, std::string trackPath) :
    Screen(frame),
    mGameRunning(false),
    mGameFinished(false)
{
    createTracks(playerCount, trackPath);
    restart();
}

void GameScreen::createTracks(size_t _playerCount, const std::string & _trackFile) {

    // Load & Setup Main Track
    Rac0r::TrackLoader trackLoader;
    std::cout << _trackFile << std::endl;
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
            //std::cout << "Offset: " << offset << std::endl;
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
            //std::cout << "Offset: " << offset << std::endl;
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
    mStartLine = sf::RectangleShape(sf::Vector2f(GameScreen::START_LINE_WIDTH, height));
    mStartLine.setOrigin(GameScreen::START_LINE_WIDTH / 2.0f, 0.0f);
    sf::Vector2f startPos = mTracks[mTracks.size()-1][0];
    sf::Vector2f nextPos = mTracks[mTracks.size()-1][1];
    sf::Vector2f startPosDir = Rac0r::normalize(nextPos - startPos);
    sf::Vector2f startPosDirOrtho = Rac0r::orthogonal(startPosDir) * (height - trackInnerOffset);
    
    mStartLine.setPosition(startPos + startPosDirOrtho);
    mStartLine.setRotation(RAD_TO_DEG(Rac0r::heading(startPosDir)));
    mStartLine.setFillColor(sf::Color::White);
    
    createPlayer();
    
    // setup countdown text
    createCountdownTimer();
    updateCountdownTimer(Rac0r::Constants::COUNTDOWN_TIMER_STRINGS[0], 1.0f);
    
    
    // hud
    for (size_t i = 0; i < mPlayers.size(); ++i) {
        // Instantiate the text label
        mPlayerLabels.emplace_back(new sf::Text);
        mPlayerLabels[i]->setFont(View::getDefaultFont());
        mPlayerLabels[i]->setCharacterSize(20);
        mPlayerLabels[i]->setStyle(sf::Text::Bold);
        mPlayerLabels[i]->setColor(Rac0r::Constants::GAME_TRACK_COLOR[i]);
        // Text and position of the label are set in layout()
        
        // Instantiate the texture and the sprite
        mPlayerKeyTextures.emplace_back(new sf::Texture);
        mPlayerKeySprites.emplace_back(new sf::Sprite);
        
        std::string filename = resourcePath() + "keys_" + std::to_string(i + 1) + ".png";
        if(!mPlayerKeyTextures[i]->loadFromFile(filename)) {
            std::cout << "Error while loading image" << std::endl;
        }
        mPlayerKeySprites[i]->setTexture(*mPlayerKeyTextures[i]);
    }
}

void GameScreen::createPlayer() {
    size_t player = 0;
    for (auto & track : mTracks) {
        Rac0r::Car * car = new Rac0r::Car(track, this);
        car->setColor(Rac0r::Constants::GAME_TRACK_COLOR[player]);
        mPlayers.push_back(new Rac0r::Player(car, Rac0r::Constants::PLAYER_KEY[player++]));
    }
}

void GameScreen::restart() {
    mGameRunning = false;
    mStartCountdown = 0;
    mCountdownTimer = mClock.getElapsedTime();
    
    for (auto player : mPlayers) {
        player->reset();
    }
}

void GameScreen::start() {
    mGameRunning = true;
    mStartCountdown = 0;
}

void GameScreen::showFinishScreen() {
    mGameFinished = true;
    
    // Find the player with the lowest total time and remember the index
    size_t winnerId = 0;
    for (int i = 1; i < mPlayers.size(); ++i) {
        if (mPlayers[i]->getTotalTime() < mPlayers[winnerId]->getTotalTime()) {
            winnerId = i;
        }
    }
    
    // Show which player won the game
    mFinishText.setString(Rac0r::Constants::GAME_PLAYER_NAME[winnerId] + L" hat gewonnen!");
    mFinishText.setFont(View::getSecondaryFont());
    mFinishText.setColor(sf::Color::White);
    mFinishText.setStyle(sf::Text::Bold);
    mFinishText.setCharacterSize(48);
    
    sf::Vector2f position;
    // After dividing by 2 we could have a .5, so we cast to int
    position.x = static_cast<unsigned int>(frame.width / 2);
    position.y = static_cast<unsigned int>(frame.height / 2);
    mFinishText.setPosition(position);
    
    // Set the origin to be the center of the text
    sf::FloatRect bounds = mFinishText.getLocalBounds();
    mFinishText.setOrigin(static_cast<unsigned int>(bounds.width / 2),
                          static_cast<unsigned int>(bounds.height / 2));
    
    // Show the time and how to return to the menu
    mFinishDetailText.setString(L"Zeit: " + std::to_wstring(mPlayers[winnerId]->getTotalTime()) + L". Drücke Esc, um zurück zum Hauptmenü zu gelangen");
    mFinishDetailText.setFont(View::getSecondaryFont());
    mFinishDetailText.setColor(sf::Color::White);
    mFinishDetailText.setStyle(sf::Text::Bold);
    mFinishDetailText.setCharacterSize(22);
    position.y += 75;
    mFinishDetailText.setPosition(position);
    bounds = mFinishDetailText.getLocalBounds();
    mFinishDetailText.setOrigin(static_cast<unsigned int>(bounds.width / 2),
                                static_cast<unsigned int>(bounds.height / 2));
}

void GameScreen::createCountdownTimer() {
    mCountdownTimerText.setString(Rac0r::Constants::COUNTDOWN_TIMER_STRINGS[0]);
    mCountdownTimerText.setFont(View::getSecondaryFont());
    mCountdownTimerText.setColor(sf::Color::White);
    mCountdownTimerText.setStyle(sf::Text::Bold);
}

void GameScreen::updateCountdownTimer(const std::string & _text, float _scale) {
    mCountdownTimerText.setString(_text);
    
    unsigned int textSize = static_cast<unsigned int>(GameScreen::COUNTDOWN_FONT_SIZE * frame.width);
    mCountdownTimerText.setCharacterSize(textSize);

    // Set position
    sf::Vector2f position;
    position.x = static_cast<int>(frame.width / 2);
    position.y = static_cast<int>(frame.height / 2);
    mCountdownTimerText.setPosition(position);
    
    // Scale the text
    sf::FloatRect bounds = mCountdownTimerText.getLocalBounds();
    mCountdownTimerText.setOrigin(bounds.width / 2, bounds.height / 2);
    mCountdownTimerText.setScale(_scale, _scale);
}

void GameScreen::layout(sf::Time elapsed) {
    // sort players by distance. this might not be the most efficient approach as the multimap is cleared and refilled for every frame. but let's not optimize prematurely. (profiling showed that about 1% of the time per frame is spent here)
    playerRanking.clear();
    size_t i = 0;
    for (Rac0r::Player* player : mPlayers) {
        playerRanking.emplace(player->getCar()->getPassedDistance(), i++);
    }
    // update hud player positions
    i = 0;
    for (const auto& rankedPlayer : playerRanking) {
        size_t playerId = rankedPlayer.second;
        
        float yPos = 15 + 28 * i++;
        mPlayerLabels[playerId]->setString(std::to_wstring(i) + L". Spieler " + Rac0r::Constants::GAME_PLAYER_NAME[playerId]);
        mPlayerLabels[playerId]->setPosition(frame.width - 220, yPos);
        mPlayerKeySprites[playerId]->setPosition(frame.width - 40, yPos + 2);
    }
    
    // show countdown
    if (!mGameRunning) {
        sf::Time current = mClock.getElapsedTime();
    
        sf::Int32 dt = current.asMilliseconds() - mCountdownTimer.asMilliseconds();
        if (dt > Rac0r::Constants::COUNTDOWN_TIMER_INTERVAL) {
            if (++mStartCountdown > Rac0r::Constants::COUNTDOWN_TIMER_STRINGS_NUM-1) {
                start();
            } else {
                mCountdownTimer = mClock.getElapsedTime();
            }
        } else {
            float scale = 1.0f  - static_cast<float>(dt) / static_cast<float>(Rac0r::Constants::COUNTDOWN_TIMER_INTERVAL);
            updateCountdownTimer(Rac0r::Constants::COUNTDOWN_TIMER_STRINGS[mStartCountdown], scale);
        }
        
        return;
    }
    
    // update player
    for (auto player : mPlayers) {
        player->update(elapsed);
    }
}

void GameScreen::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // Render Tracks
    for (auto & trackDrawable : mTrackDrawables) {
        trackDrawable.draw(target, states);
    }
    
    target.draw(mStartLine, states);
    
    // Draw the HUD
    for (auto& playerLabel : mPlayerLabels) {
        target.draw(*playerLabel, states);
    }
    for (auto& keySprite : mPlayerKeySprites) {
        target.draw(*keySprite, states);
    }
    
    // Draw the countdown
    if (!mGameRunning) {
        target.draw(mCountdownTimerText, states);
        return;
    }
    
    // draw players
    for (auto player : mPlayers) {
        player->draw(target, states);
    }
    
    // Draw the win screen
    if (mGameFinished) {
        target.draw(mFinishText, states);
        target.draw(mFinishDetailText, states);
    }
}


void GameScreen::onCarDriftedOffTrack(Rac0r::Car & _car) {
    // NODE: Player handles this by himself...
}

void GameScreen::onCarMovedThroughStart(Rac0r::Car & _car) {
    size_t finishedPlayers = 0;
    for (auto & player : mPlayers) {
        if (player->getCar() == &_car) {
        	player->nextLap();
        }
        if (player->isFinish()) {
            ++finishedPlayers;
        }
    }
    if (finishedPlayers >= mPlayers.size()) {
        showFinishScreen();
    }
}

void GameScreen::onCarStartedFromStart(Rac0r::Car & _car) {
}

void GameScreen::handleEvent(sf::Event event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        // Escape pressed : exit
        quit = true;
    }
}

