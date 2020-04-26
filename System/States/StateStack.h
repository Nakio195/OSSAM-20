#ifndef STATESTACK_H
#define STATESTACK_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>
#include <assert.h>

#include "System/States/State.h"
#include "System/States/StateIdentifiers.h"

class State;

class StateStack
{
    public:
        enum Action
        {
            Push,
            Pop,
            Clear
        };

    public:
        StateStack(State::Context context);

        template <typename DerviedState>
        void registerState(States::ID stateId);  // Initialise la factories d'un state::id

        void update(sf::Time dt);
        void draw();
        void handleEvent(const sf::Event event);

        void pushState(States::ID stateId);
        void popState();
        void clearStates();

        bool isEmpty();

    private:
        State::ptr createState(States::ID stateId);
        void applyPendingChanges();

    private:
        struct PendingChange
        {
            explicit PendingChange(Action action, States::ID stateID = States::None);
            Action action;
            States::ID stateId;
        };

    private:
        std::vector<State::ptr> mStack;
        std::vector<PendingChange> mPendingList;
        State::Context mContext;
        std::map<States::ID, std::function<State::ptr()>> mFactories;


};

template <typename DerviedState>
void StateStack::registerState(States::ID stateId)
{
    mFactories[stateId] = [this] ()
    {
        return State::ptr(new DerviedState(*this, mContext));
    };
}


#endif // STATESTACK_H
