#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Ressources/RessourceHolder.h"
#include "System/World.h"
#include "System/Player.h"

#include "System/States/StateStack.h"

class GameState : public State
{
    public:
        GameState(StateStack& stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time elapsedTime);
        virtual bool handleEvent(const sf::Event &event);

    private:
        World mWorld;
        Player& mPlayer;
        Timer mEndTimer;
        sf::RectangleShape mBlendShape;
};

#endif // GAME_H
