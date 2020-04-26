#include "System/States/PauseState.h"
#include "System/Utilities.h"


PauseState::PauseState(StateStack& stack, Context context) : State(stack, context)
{
    sf::Vector2u windowSize = context.window->getSize();

    mPauseText.setCharacterSize(60);
    mPauseText.setString("PAUSE");
    mPauseText.setFont(context.fonts->get(Fonts::KLM));
    centerOrigin(mPauseText);
    mPauseText.setPosition(sf::Vector2f(windowSize/ 2u));

}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape shape(sf::Vector2f(window.getSize()));
    shape.setFillColor(sf::Color(0, 0, 0, 150));
    shape.setPosition(0.0, 0.0);

    window.setView(window.getDefaultView());
    window.draw(shape);
    window.draw(mPauseText);
}

bool PauseState::update(sf::Time )
{
    return false;
}

bool PauseState::handleEvent(const sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
    }
    return false;
}
