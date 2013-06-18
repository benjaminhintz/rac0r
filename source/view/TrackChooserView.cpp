//
//  TrackChooserView.cpp
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

#include "TrackChooserView.h"
#include "ResourcePath.hpp"


TrackChooserView::TrackChooserView(const Rect& frame) : View(frame) {
    // Get a list of all tracks
    Rac0r::TrackFileManager fileManager;
    tracks = fileManager.getTrackList();
    
    // Load textures
    arrowDownTexture.loadFromFile(resourcePath() + "arrowDown.png");
    arrowUpTexture.loadFromFile(resourcePath() + "arrowUp.png");
    
    // Initialize arrows and the track image
    arrowRight.setTexture(arrowUpTexture);
    arrowRight.rotate(90);
    addChild(arrowRight);
    
    arrowLeft.setTexture(arrowDownTexture);
    arrowLeft.rotate(90);
    addChild(arrowLeft);

    addChild(track);
    
    // Select the first track
    if (tracks.size() > 0) {
        setTrack(0);
    }
    // Calculate the initial layout. However, it will be recalculated whenever View's setSize() is called.
    layoutChildviews();
}

void TrackChooserView::setTrack(int newTrackNumber) {
    if (newTrackNumber >= 0 && newTrackNumber < tracks.size()) {
        trackNumber = newTrackNumber;
        
        // Update the track preview
        trackTexture = sf::Texture();
        std::string filename = tracks.at(trackNumber).getImageFile();
        if (!trackTexture.loadFromFile(filename)){
            std::cout << "Error while loading the track's preview image" << std::endl;
        }
        track.setTexture(trackTexture);
    }
}

// Handle input events
void TrackChooserView::handleEvent(sf::Event event) {
    bool pressed = (event.type == sf::Event::KeyPressed);
    bool released = (event.type == sf::Event::KeyReleased);

    // Select the next track
    if (pressed && event.key.code == sf::Keyboard::Right) {
        setTrack(trackNumber + 1);
        // Move the arrow
        layoutChildviews();
        arrowRight.move(6,0);
    } else if (released && event.key.code == sf::Keyboard::Right) {
        // Reset the arrow
        layoutChildviews();
    }
    
    // Select the previous track
    if (pressed && event.key.code == sf::Keyboard::Left) {
        setTrack(trackNumber - 1);
        // Move the arrow
        layoutChildviews();
        arrowLeft.move(-6, 0);
    } else if (released && event.key.code == sf::Keyboard::Left) {
        // Reset the arrow
        layoutChildviews();
    }
}

// This is called whenever the View's size is set
void TrackChooserView::layoutChildviews() {
    sf::Vector2f position;
    sf::Vector2f size;
    
    track.setPosition(frame.width / 2 - 320, 0);
    
    // Arrows
    size = sf::Vector2f(arrowUpTexture.getSize());
    position.x = frame.width - size.x + 430;
    position.y = 150;
    arrowRight.setPosition(position);
    
    size = sf::Vector2f(arrowDownTexture.getSize());
    position.x -= 740;
    arrowLeft.setPosition(position);
}

std::string TrackChooserView::getTrackPath() {
    return tracks.at(trackNumber).getTrackFile();
}
