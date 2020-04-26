#ifndef MENUSTATE_H
#define MENUSTATE_H


#include "Ressources/RessourceHolder.h"
#include "System/World.h"
#include "System/Player.h"

#include "System/States/StateStack.h"

class MenuState : public State
{
    public:
        MenuState(StateStack& stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time elapsedTime);
        virtual bool handleEvent(const sf::Event &event);
};

#endif // MENUSTATE_H
