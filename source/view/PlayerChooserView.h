//
//  PlayerChooserView.h
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

#ifndef __Rac0r__PlayerChooserView__
#define __Rac0r__PlayerChooserView__

#include "View.h"

class PlayerChooserView : public View {
public:
    PlayerChooserView(std::string noun, int minValue, int maxValue, const Rect& frame = Rect(0, 0, 0, 0));
    virtual ~PlayerChooserView() = default;
    
    int getValue();
    void setValue(int newValue);
    virtual void handleEvent(sf::Event event);
    
protected:
    virtual void layoutChildviews();

private:
    int minValue;
    int maxValue;
    int value;
    std::string noun;
    sf::Texture arrowDownTexture;
    sf::Texture arrowUpTexture;
    sf::Sprite arrowUp;
    sf::Sprite arrowDown;
    sf::Text textLabel;
};

#endif /* defined(__Rac0r__PlayerChooserView__) */
