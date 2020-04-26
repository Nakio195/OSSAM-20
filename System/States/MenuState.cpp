#include "System/States/MenuState.h"

MenuState::MenuState(StateStack& stack, Context context) : State(stack, context)
{

}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;

}

bool MenuState::update(sf::Time dt)
{

}

bool MenuState::handleEvent(const sf::Event &event)
{

    return true;
}
