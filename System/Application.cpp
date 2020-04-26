#include "System/Application.h"
#include "System/States/GameState.h"
#include "System/States/TitleState.h"
#include "System/States/LoadingState.h"
#include "System/States/MenuState.h"
#include "System/States/PauseState.h"


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
    : mWindow(sf::VideoMode(1600, 900), sf::String("OSSAM"), sf::Style::Default, sf::ContextSettings(2, 1, 4, 1))
    , mTextures()
    , mFonts()
    , mMusicPlayer()
    , mPlayer()
    , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusicPlayer, mSoundPlayer))
{
    mWindow.setKeyRepeatEnabled(false);
    mWindow.setVerticalSyncEnabled(true);

    mFonts.load(Fonts::Main, "Ressources/consola.ttf");
    mFonts.load(Fonts::KLM, "Ressources/TYPO KLM.ttf");
    mTextures.load(Textures::TitleScreen, "Ressources/Title.jpg");
    mTextures.load(Textures::TitleScreen2, "Ressources/Title2.jpg");

    registerStates();
    mStateStack.pushState(States::Title);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty before update() call
            if (mStateStack.isEmpty())
                mWindow.close();
        }
        render();
    }
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();

        if(event.type == sf::Event::LostFocus)
            mStateStack.pushState(States::Pause);
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();

    mStateStack.draw();

    mWindow.display();
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
}
