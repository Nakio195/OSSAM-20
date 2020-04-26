#include "System/Player.h"
#include <functional>

#include <iostream>
using namespace std::placeholders;


struct SpaceshipMover
{
    SpaceshipMover(float x, float y) : velocity(x, y)
    {
    }

    void operator() (Spaceship& spaceship, sf::Time ) const
    {
        sf::Vector2f newVelocity = velocity * spaceship.getStats().speed;
        spaceship.applyForce(newVelocity, Force::Impulse, sf::seconds(0.2f));
    }

    sf::Vector2f velocity;
};

Player::Player()
{
    mKeyBinding[sf::Keyboard::Q] = MoveLeft;
    mKeyBinding[sf::Keyboard::D] = MoveRight;
    mKeyBinding[sf::Keyboard::Z] = MoveForward;
    mKeyBinding[sf::Keyboard::S] = MoveBack;
    mKeyBinding[sf::Keyboard::Space] = Fire;
    mKeyBinding[sf::Keyboard::LShift] = LaunchMissile;

    mActionBinding[MoveLeft].category = Category::PlayerSpaceship;
    mActionBinding[MoveForward].category = Category::PlayerSpaceship;
    mActionBinding[MoveRight].category = Category::PlayerSpaceship;
    mActionBinding[MoveBack].category = Category::PlayerSpaceship;
    mActionBinding[MoveLeft].action = derivedAction<Spaceship>(SpaceshipMover(-1.f, 0.f));
    mActionBinding[MoveForward].action = derivedAction<Spaceship>(SpaceshipMover(0.f, -1.f));
    mActionBinding[MoveRight].action = derivedAction<Spaceship>(SpaceshipMover(1.f, 0.f));
    mActionBinding[MoveBack].action = derivedAction<Spaceship>(SpaceshipMover(0.f, 1.f));

    mActionBinding[Fire].action = derivedAction<Spaceship>(std::bind(&Spaceship::shoot, std::placeholders::_1, Weapon::Main));
    mActionBinding[LaunchMissile].action = derivedAction<Spaceship>(std::bind(&Spaceship::shoot, _1, Weapon::Secondary));
    mActionBinding[Fire].category = Category::PlayerSpaceship;
    mActionBinding[LaunchMissile].category = Category::PlayerSpaceship;
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
    for(auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
    {
        if(itr->second == action)
            mKeyBinding.erase(itr++);
        else
            ++itr;
    }

    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for(auto key : mKeyBinding)
    {
        if(key.second == action)
            return key.first;
    }

    return sf::Keyboard::Unknown;
}

void Player::handleEvent(const sf::Event &event, CommandQueue &Commands)
{
    if(event.type == sf::Event::KeyPressed)
    {
        auto found = mKeyBinding.find(event.key.code);

        if(found != mKeyBinding.end() && !isRealTimeAction(found->second))
            Commands.push(mActionBinding[found->second]);
    }
}

void Player::handleRealTimeInput(CommandQueue &Commands)
{
    for(auto pair : mKeyBinding)
    {
        if(sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
            Commands.push(mActionBinding[pair.second]);
    }

}

bool Player::isRealTimeAction(Action action)
{
    switch(action)
    {
        case MoveRight:
        case MoveLeft:
        case MoveBack:
        case MoveForward:
        case Fire:
            return true;

        default:
            return false;

    }
}
