#ifndef PAUSESTATE_H
#define PAUSESTATE_H


#include "Ressources/RessourceHolder.h"
#include "System/World.h"
#include "System/Player.h"

#include "System/States/StateStack.h"

class TextNode;

class PauseState : public State
{
    public:
        PauseState(StateStack& stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time elapsedTime);
        virtual bool handleEvent(const sf::Event &event);

    private:
        sf::Text mPauseText;
};

#endif // PAUSESTATE_H
