#include "System/States/GameState.h"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.soundPlayer)
, mPlayer(*context.player)
{
    mEndTimer.setMode(Timer::OneShot);
    mEndTimer.setPeriod(sf::seconds(6));

    mBlendShape.setSize(sf::Vector2f(context.window->getSize()));
    mBlendShape.setFillColor(sf::Color(0, 0, 0, 0));

    context.musicPlayer->stop();
    context.musicPlayer->play(Music::Level1);
    context.musicPlayer->setVolume(1.f);
}

void GameState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    //mWorld.printSceneGraph();
    mWorld.draw();

    if(mEndTimer.isRunning())
    {
        window.setView(window.getDefaultView());
        window.draw(mBlendShape);
    }
}

bool GameState::update(sf::Time dt)
{
    if(!mEndTimer.isRunning())
        mWorld.update(dt);
    else
    {
        mWorld.update(sf::seconds(dt.asSeconds()/mEndTimer.getPeriod()*(1-mEndTimer.getProgression())));
        mBlendShape.setFillColor(sf::Color(255, 255, 255, static_cast<unsigned char>(255.f*mEndTimer.getProgression())));
    }

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealTimeInput(commands);

    if(!mWorld.hasAlivePlayer())
    {
        if(mEndTimer.isRunning())
            mEndTimer.Count(dt);
        else
            mEndTimer.StartTimer();

        if(mEndTimer.Triggered())
        {
            requestStackPop();
            requestStackPush(States::Title);
        }
    }

    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        requestStackPush(States::Pause);

    return true;
}
