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
    
    
    track.setPosition(frame.width/2 - 100, 100);
    track.setFillColor(sf::Color::White);
    track.setSize(sf::Vector2f(200,100));
    
    start.setString("test");
    start.setColor(sf::Color::White);
    start.setPosition(10, 10);
    start.setFont(font);
    
    player.setString("x player");
    player.setColor(sf::Color::White);
    player.setPosition(10, 50);
    player.setFont(font);
    
    logo.setPosition(200,200);
    logo.setSize(sf::Vector2f(200,200));
    logo.setFillColor(sf::Color::White);

    
    sf::Texture texture;
    texture.loadFromFile( resourcePath() + "logo.png");
    if (!texture.loadFromFile( resourcePath() + "logo.png"))
    {
        // error...
    }

    
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
        }
        cout << "ein Spieler mehr " << Screen::playerCount << endl;
    }
    else if (up && event.key.code == sf::Keyboard::Down)
    {
        if (Screen::playerCount > 1){
            Screen::playerCount--;
        }
        cout << "ein Spieler weniger " << Screen::playerCount << endl;
    }
    else if (up && event.key.code == sf::Keyboard::Right)
    {
        if (Screen::trackNumber < 5){
            player.setString(tracks.at(trackNumber).getTrackFile());
            Screen::trackNumber++;
        }
        cout << "Ein Track weiter " << Screen::trackNumber << endl;
    }
    else if (up && event.key.code == sf::Keyboard::Left)
    {
        if (Screen::trackNumber > 1){
            Screen::trackNumber--;
        }
        cout << "Ein Track zurück " << Screen::trackNumber << endl;
    }
    if (up && event.key.code == sf::Keyboard::Return) {
        Screen::finished = true;
    }
}

void MenuScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(logo, states);
    target.draw(track, states);
    target.draw(player, states);
    target.draw(start, states);
}


