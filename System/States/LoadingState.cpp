#include "System/States/LoadingState.h"

LoadingState::LoadingState(StateStack& stack, Context context) : State(stack, context)
{

}

void LoadingState::draw()
{
    //sf::RenderWindow& window = *getContext().window;
}

bool LoadingState::update(sf::Time )
{
    return true;
}

bool LoadingState::handleEvent(const sf::Event& )
{

    return true;
}
