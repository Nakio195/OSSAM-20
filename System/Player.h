#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <SFML/Graphics.hpp>
#include "System/Commands/Command.h"
#include "Entities/Spaceship.h"

class Player
{
    public:
        enum Action
        {
            MoveRight,
            MoveLeft,
            MoveForward,
            MoveBack,
            Fire,
            LaunchMissile,
            ActionCount
        };

    public:
        Player();

        void assignKey(Action action, sf::Keyboard::Key key);
        sf::Keyboard::Key getAssignedKey(Action action) const;

        void handleEvent(const sf::Event& event, CommandQueue& Commands);
        void handleRealTimeInput(CommandQueue& Commands);

    private:
        static bool isRealTimeAction(Action action);

    private:
        std::map<sf::Keyboard::Key, Action> mKeyBinding;
        std::map<Action, Command> mActionBinding;
};

#endif // PLAYER_H
