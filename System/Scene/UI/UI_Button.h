#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

#include "../../UserInterface.h"

class UI_Button : public UserInterface
{
    public:
        enum States{Enabled, Disabled, Clicked, Released};

    public:
        UI_Button(std::string Path, UserInterface *pParent);
        bool isTriggered();
        void setState(unsigned int pState);

        void setRelativePosition(float x, float y);
        void setRelativePosition(sf::Vector2f RelativePosition);
        sf::Vector2f getRelativePosition();

        void Display(sf::RenderWindow &Window);
        void HandleEvent(sf::Event &Event);

    private:
        UserInterface *Parent;
        sf::Texture Background;
        sf::Vector2f Position;
        unsigned int State;
        bool Triggered;
};

#endif // UI_BUTTON_H
