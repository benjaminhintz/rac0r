//
//  View.h
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

#ifndef __Rac0r__View__
#define __Rac0r__View__

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>


// Typedefs
class View;
//typedef std::shared_ptr<View> view_ptr;
typedef sf::Rect<float> Rect;

// Possible view states
enum class ViewState { normal, highlighted, activated };



class View : public sf::Transformable, public sf::Drawable {
public:
    View(const Rect& frame = Rect(0, 0, 0, 0));
    virtual ~View() = default;
    
    void setState(ViewState newState);
    void setSize(float x, float y);
    sf::Vector2f getSize();
    
protected:
    // This childView stuff is only for easier drawing. You still need to retain
    // that object at all times and you have to manage its memory
    void addChild(sf::Drawable& child);
    // Views can have different style sets for easier switching between states
    virtual void applyStyle() {};
    // Calculate all subviews' positions
    virtual void layoutChildviews() {};
    // Handle input events
    virtual void handleEvent(sf::Event event) {};
    // Draw all subviews
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Some resource helper functions that all views can use
    static const sf::Font& getDefaultFont();

    // Get Font Path related to system we running on
    static const std::string & getFontPath();
    
    
protected:
    // Represents the top left corner and the size of the view
    Rect frame;
    ViewState state;
    std::vector<sf::Drawable*> childViews;
};

#endif /* defined(__Rac0r__View__) */
