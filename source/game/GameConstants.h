//
//  Game.h
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

#ifndef __Rac0r__Game__
#define __Rac0r__Game__

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>


namespace Rac0r {

// Game constants
namespace Constants {
    
    constexpr static const size_t   COUNTDOWN_TIMER_INTERVAL                                    =   1000;
    constexpr static const size_t   COUNTDOWN_TIMER_STRINGS_NUM                                 =   4;

    static const std::string        COUNTDOWN_TIMER_STRINGS[COUNTDOWN_TIMER_STRINGS_NUM]        =   { "3", "2", "1", "START" };
    
    constexpr static const size_t   GAME_MAX_LAPS                                               =   3;
    constexpr static const size_t   GAME_MAX_PLAYERS                                            =   5;

    constexpr static const bool		PLAY_SOUND													=	true;

    static const sf::Color          GAME_TRACK_COLOR[GAME_MAX_PLAYERS]                          =   { sf::Color(0,153,205,153),
                                                                                                        sf::Color(102, 153, 0, 153),
                                                                                                        sf::Color(153, 51, 204, 153),
                                                                                                        sf::Color(255, 136, 0, 153),
                                                                                                        sf::Color(204, 0, 0, 153)
                                                                                                    };

    static const sf::Keyboard::Key  PLAYER_KEY[GAME_MAX_PLAYERS]                                =   { sf::Keyboard::Q,
                                                                                                        sf::Keyboard::X,
                                                                                                        sf::Keyboard::T,
                                                                                                        sf::Keyboard::N,
                                                                                                        sf::Keyboard::P
                                                                                                    };
    
    constexpr static const size_t   PLAYER_OFF_TRACK_RESET_INTERVAL                             =   1000;
}

}

#endif /* defined(__Rac0r__Game__) */
