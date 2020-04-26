#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <SFML/Graphics.hpp>

class UserInterface : public sf::Sprite
{
    public:
        UserInterface();
        virtual ~UserInterface();
        virtual void Display(sf::RenderWindow &Window);
        virtual void HandleEvent(sf::Event &Event);
};

#endif // USERINTERFACE_H
