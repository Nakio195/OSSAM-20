#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H


#include "Ressources/RessourceHolder.h"
#include "System/World.h"
#include "System/Player.h"

#include "System/States/StateStack.h"

class LoadingState : public State
{
    public:
        LoadingState(StateStack& stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time elapsedTime);
        virtual bool handleEvent(const sf::Event &event);
};

#endif // LOADINGSTATE_H
