#ifndef COMMAND_H
#define COMMAND_H

#include <queue>
#include <assert.h>
#include <functional>

#include <SFML/Graphics.hpp>

#include "System/Commands/Category.h"

class SceneNode;

struct Command
{
    typedef std::function<void(SceneNode&, sf::Time)> Action;

    Command();

    Action action;
    unsigned int category;
    unsigned long id;
};


class CommandQueue
{
    public:
        CommandQueue();

        void push(const Command& command);
        Command pop();

        bool isEmpty();

    private:
        std::queue<Command> mQueue;

};

template <typename GameObject, typename Function>
Command::Action derivedAction(Function fn)
{
    return [=] (SceneNode& node, sf::Time dt)
    {
        // Check if cast is safe
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        // Downcast node and invoke function on it
        fn(static_cast<GameObject&>(node), dt);
    };
}

#endif // COMMAND_H
