#include "System/States/TitleState.h"

TitleState::TitleState(StateStack& stack, Context context) : State(stack, context)
{
    sf::RenderWindow& window = *getContext().window;
    sf::Vector2u windowSize = getContext().window->getSize();

    sf::Texture& background = getContext().textures->get(Textures::TitleScreen);
    mBackgroundSprite.setTexture(background);
    mBackgroundSprite.setOrigin(mBackgroundSprite.getTexture()->getSize().x/2, mBackgroundSprite.getTexture()->getSize().y/2);
    mBackgroundSprite.setPosition(sf::Vector2f(windowSize /2u));
    mBackgroundSprite.scale(0.3f, 0.3f);

    sf::Texture& background2 = getContext().textures->get(Textures::TitleScreen2);
    mBackgroundSprite2.setTexture(background2);
    mBackgroundSprite2.setOrigin(mBackgroundSprite2.getTexture()->getSize().x/2, mBackgroundSprite2.getTexture()->getSize().y/2);
    mBackgroundSprite2.setPosition(sf::Vector2f(windowSize /2u));
    mBackgroundSprite2.scale(0.7f, 0.7f);

    mTitleView.setSize(sf::Vector2f(window.getSize()));
    mTitleView.setCenter(sf::Vector2f(windowSize /2u));

    mBlendShape.setSize(sf::Vector2f(window.getSize()));
    mBlendShape.setFillColor(sf::Color(255,255,255,255));
    mBlend = 255.f;
    mBlendOver = true;
    mBlendDirection = true;
    mCurrentTitle = 0;
    mTitleCount = 2;

    context.musicPlayer->play(Music::TitleTheme);
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.setView(window.getDefaultView());

    if(mCurrentTitle == 0)
        window.draw(mBackgroundSprite);
    if(mCurrentTitle == 1)
        window.draw(mBackgroundSprite2);

    window.draw(mBlendShape);
}

bool TitleState::update(sf::Time dt)
{
    if(mBlend > 0.f)
        mBlend -= 32*dt.asSeconds();
    if(mBlend <= 0.f)
    {
        mBlendOver = true;
        mBlendDirection = !mBlendDirection;
        mBlend = 255.f;
    }

    if(mBlendOver && !mBlendDirection)
    {
        if(++mCurrentTitle == mTitleCount)
            mCurrentTitle = 0;
    }

    if(mBlendOver)
        mBlendOver = false;

    if(mBlendDirection)
        mBlendShape.setFillColor(sf::Color(255,255,255, 255-static_cast<unsigned char>(mBlend)));
    if(!mBlendDirection)
        mBlendShape.setFillColor(sf::Color(255,255,255, static_cast<unsigned char>(mBlend)));

    return true;
}

bool TitleState::handleEvent(const sf::Event &event)
{
    if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
    }

    else if(event.type == sf::Event::KeyReleased)
    {
        requestStackPop();
        requestStackPush(States::Game);
    }

    return true;
}
