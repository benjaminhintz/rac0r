//
//  MenuScreen.cpp
//  Rac0r
//
//  Created by Jannes on Jun/13/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "MenuScreen.h"
#include "ResourcePath.hpp"

using namespace std;

MenuScreen::MenuScreen(const Rect& frame) : Screen(frame) {
    Rac0r::TrackFileManager fileManager;
    tracks = fileManager.getTrackList();
    std::cout << tracks.size() << " tracks loaded" << endl;
    init();
}

void MenuScreen::init() {
    static sf::Font font;
    font.loadFromFile(resourcePath() +  "Tahoma.ttf");
    
    description.setString("beschreibung + Tastaturbelegung");
    description.setPosition(10,100);
    description.setColor(sf::Color::White);
    description.setFont(font);
    
    track.setPosition(frame.width/2 - 100, 100);
    track.setFillColor(sf::Color::White);
    track.setSize(sf::Vector2f(200,100));
    
    start.setString("start");
    start.setColor(sf::Color::White);
    start.setPosition(10, 10);
    start.setFont(font);
    
    player.setString("1 player");
    player.setColor(sf::Color::White);
    player.setPosition(10, 50);
    player.setFont(font);
    
    if (!logoTexture.loadFromFile( resourcePath() + "logo.png")) {
        cerr << "Error while loading image" << endl;
        return;
    }
    logoSprite.setTexture(logoTexture);
    logoSprite.setPosition(200, 200);
}


void MenuScreen::handleEvent(sf::Event event) {
    bool down = (event.type == sf::Event::KeyPressed);
    bool up = (event.type == sf::Event::KeyReleased);
    if (down && event.key.code == sf::Keyboard::Down) {
    }
    else if (up && event.key.code == sf::Keyboard::Up)
    {
        if (Screen::playerCount < 5){
            Screen::playerCount++;
            string playerCountStr;
            ostringstream convert;
            convert << playerCount;
            playerCountStr = convert.str();
            player.setString(playerCountStr + " player");
        }
        cout << "ein Spieler mehr " << Screen::playerCount << endl;
    }
    else if (up && event.key.code == sf::Keyboard::Down)
    {
        if (Screen::playerCount > 1){
            Screen::playerCount--;
            string playerCountStr;            
            ostringstream convert;
            convert << playerCount;
            playerCountStr = convert.str();
            player.setString(playerCountStr + " player");
            
        }
        cout << "ein Spieler weniger " << Screen::playerCount << endl;
    }
    else if (up && event.key.code == sf::Keyboard::Right)
    {
        if (trackNumber < tracks.size() - 1){
            //TODO textur neu setzen
//            sf::Texture texture;
//            texture.loadFromFile(tracks.at(trackNumber).getImageFile());
//            track.setTexture(&texture);
            trackNumber++;
            std::cout << tracks.at(trackNumber).getTrackFile() << std::endl;
        }
        cout << "Ein Track weiter " << Screen::trackPath << endl;
    }
    else if (up && event.key.code == sf::Keyboard::Left)
    {
        if (trackNumber > 0){
            trackNumber--;
            std::cout << tracks.at(trackNumber).getTrackFile() << std::endl;
        }
        cout << "Ein Track zurück " << Screen::trackPath << endl;
    }
    if (up && event.key.code == sf::Keyboard::Return) {
        Screen::trackPath = tracks.at(trackNumber).getTrackFile();
        Screen::finished = true;
    }
}

void MenuScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(description);
    target.draw(track, states);
    target.draw(player, states);
    target.draw(start, states);
    target.draw(logoSprite, states);
}


