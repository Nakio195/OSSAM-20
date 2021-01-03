#include "UI_Button.h"

/**
 * @brief UI_Button::UI_Button
 * @param Path
 * @param pParent
 */

UI_Button::UI_Button(std::string Path, UserInterface *pParent)
{
    Background.loadFromFile(Path);
    sf::Sprite::setTexture(Background);
    Parent = pParent;

    State = UI_Button::Enabled;
    Triggered = false;
}

bool UI_Button::isTriggered()
{
    if(Triggered)
    {
        Triggered = false;
        return true;
    }

    else
        return false;
}

void UI_Button::Display(sf::RenderWindow &Window)
{
    setPosition(Parent->getPosition() + Position);
    Window.draw(*this);//Window.draw();
}

void UI_Button::setRelativePosition(sf::Vector2f RelativePosition)
{
    Position = RelativePosition;
}

void UI_Button::setRelativePosition(float x, float y)
{
    Position = sf::Vector2f(x, y);
}

sf::Vector2f UI_Button::getRelativePosition()
{
    return Position;
}

void UI_Button::setState(unsigned int pState)
{
    if(pState == UI_Button::Enabled)
    {
        this->setColor(sf::Color(0xFF, 0xFF, 0xFF));
        State = pState;
    }

    else if(pState == UI_Button::Disabled)
    {
        this->setColor(sf::Color(0x80, 0x80, 0x80));
        State = pState;
    }

    else if(pState == UI_Button::Clicked)
    {
        this->setColor(sf::Color(0x80, 0xFF, 0x80));
        State = pState;
    }

    else if(pState == UI_Button::Released)
    {
        this->setColor(sf::Color(0xFF, 0xFF, 0xFF));
        State = pState;
    }
}

void UI_Button::HandleEvent(sf::Event &Event)
{
    switch(Event.type)
    {
        case sf::Event::MouseButtonPressed:
            if(Event.mouseButton.button == sf::Mouse::Left)
            {
                if(this->getGlobalBounds().contains(Event.mouseButton.x, Event.mouseButton.y))
                {
                    setState(UI_Button::Clicked);
                }
            }
            break;

        case sf::Event::MouseButtonReleased:
            if(Event.mouseButton.button == sf::Mouse::Left)
            {
                if(State == UI_Button::Clicked)
                {
                    setState(UI_Button::Released);
                    Triggered = true;
                }
            }
            break;

        default:
            break;
    }
}
