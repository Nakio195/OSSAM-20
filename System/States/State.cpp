#include "System/States/State.h"
#include "System/States/StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer &musicPlayer, SoundPlayer& soundPlayer)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, player(&player)
, musicPlayer(&musicPlayer)
, soundPlayer(&soundPlayer)
{
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
    mStack->pushState(stateID);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStateClear()
{
    mStack->clearStates();
}

State::Context State::getContext() const
{
    return mContext;
}
