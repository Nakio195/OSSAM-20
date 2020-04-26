#include "System/States/StateStack.h"


StateStack::StateStack(State::Context context): mStack(), mPendingList(), mContext(context), mFactories()
{

}


void StateStack::update(sf::Time dt)
{
    // Iterate from top to bottom, stop as soon as update() returns false
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
            break;
    }

    applyPendingChanges();
}

void StateStack::draw()
{
    for(State::ptr& state : mStack)
    {
        state->draw();
    }
}

void StateStack::handleEvent(const sf::Event event)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateId)
{
    mPendingList.push_back(PendingChange(Push, stateId));
}

void StateStack::popState()
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
    mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty()
{
    return mStack.empty();
}


State::ptr StateStack::createState(States::ID stateId)
{
    auto state = mFactories.find(stateId);

    assert(state != mFactories.end());

    return state->second();
}

void StateStack::applyPendingChanges()
{
    for(auto pending : mPendingList)
    {
        switch(pending.action)
        {
            case Pop:
                mStack.pop_back();
                break;

            case Push:
                mStack.push_back(createState(pending.stateId));
                break;

            case Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action act, States::ID state) : action(act), stateId(state)
{
}
