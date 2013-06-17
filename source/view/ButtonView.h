//
//  ButtonView.h
//  Rac0r
//
//  Created by Jannes on Jun/16/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__ButtonView__
#define __Rac0r__ButtonView__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "ResourcePath.hpp"
#include "View.h"

class ButtonView : public View {
public:
    ButtonView(const Rect& frame = Rect(0, 0, 0, 0));
    virtual ~ButtonView() = default;
    
    void setFont(const sf::Font& font) {
        textLabel.setFont(font);
    }
    void setText(const std::string& text) {
        textLabel.setString(text);
    }
    static const sf::Font& getDefaultFont();
    
protected:
    virtual void applyStyle();
    virtual void layout();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    
private:
    sf::RectangleShape background;
    sf::Text textLabel;
    sf::Color backgroundNormal;
    sf::Color backgroundActivated;
    sf::Color textHighlighted;
    sf::Color textActivated;
};

#endif /* defined(__Rac0r__ButtonView__) */
