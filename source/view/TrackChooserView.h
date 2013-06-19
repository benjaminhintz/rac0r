//
//  TrackChooserView.h
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

#ifndef __Rac0r__TrackChooserView__
#define __Rac0r__TrackChooserView__

#include <string>
#include "View.h"
#include "../track/TrackFileManager.h"

class TrackChooserView : public View {
public:
    TrackChooserView(const Rect& frame = Rect(0,0,0,0));
    virtual ~TrackChooserView() = default;

    // This value is read from the main loop
    std::string getTrackPath();
    void setTrack(int newTrack);
    virtual void handleEvent(sf::Event event);
    
protected:
    virtual void layoutChildviews();
    
private:
    int trackNumber = -1;
    std::vector<Rac0r::TrackFile> tracks;
    
    sf::Texture trackTexture;
    sf::Sprite track;
    sf::Texture arrowDownTexture;
    sf::Texture arrowUpTexture;
    sf::Sprite arrowRight;
    sf::Sprite arrowLeft;
};


#endif /* defined(__Rac0r__TrackChooserView__) */
