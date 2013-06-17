//
//  View.h
//  Rac0r
//
//  Created by Jannes on Jun/16/13.
//  Copyright (c) 2013 Jan Schulte. All rights reserved.
//

#ifndef __Rac0r__View__
#define __Rac0r__View__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>


// Typedefs
class View;
typedef std::shared_ptr<View> view_ptr;
typedef sf::Rect<float> Rect;
enum class ViewState { normal, highlighted, activated };

class View : public sf::Transformable, public sf::Drawable {
public:
    View(const Rect& frame = Rect(0, 0, 0, 0));
    virtual ~View() = default;
    
    void setState(ViewState newState);
    void setSize(float x, float y);
    void addChild(view_ptr child);
    
protected:
    virtual void applyStyle() {};
    virtual void layout() {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ViewState state;
    sf::Vector2f size;
    Rect frame;
    std::vector<view_ptr> childViews;
};

#endif /* defined(__Rac0r__View__) */
