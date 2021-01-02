#include "AsteroidGenerator.h"

#include <iostream>

AsteroidGenerator::AsteroidGenerator(const TextureHolder& textures) : mTextures(textures)
{
}

void AsteroidGenerator::updateCurrent(sf::Time dt, CommandQueue &Commands)
{
    mTimer.Count(dt);

    if(mTimer.Triggered())
    {
        trigger(dt, Commands);
        start();
    }
}

unsigned int AsteroidGenerator::getSceneCategory() const
{
    return Category::CommandGenerator;
}

sf::FloatRect AsteroidGenerator::getBoundingRect() const
{
    return getWorldTransform().transformRect(sf::FloatRect(0, 0, 20, 20));
}

void AsteroidGenerator::start()
{
    mTimer.StartTimer(frequency());
}

void AsteroidGenerator::pause(bool paused)
{
    if(paused)
        mTimer.PauseTimer();
    else
        mTimer.ReleaseTimer();
}

void AsteroidGenerator::resume()
{
    pause(false);
}

void AsteroidGenerator::stop()
{
    mTimer.StopTimer();
}

void AsteroidGenerator::trigger(sf::Time dt, CommandQueue &Commands)
{
    std::unique_ptr<Debris> debris(new Debris(Debris::Asteroid, mTextures));

    float Spin = spin();
    float Angle = angle();
    float Speed = speed();

    if(Spin > 0 && Spin < 20)
        Spin = 20.f;
    if(Spin < 0 && Spin > -20)
        Spin = -20.f;

    debris->setSpin(spin());
    debris->setSpeed(Speed);
    debris->applyForce(fromAngle(Angle)*Speed, Force::Constant);

    float debrisScale = scale();
    debris->scale(sf::Vector2f(1.f, 1.f)*debrisScale);
    debris->takeDamage(static_cast<int>(debris->getHealthPoints()*(1.f-debrisScale)));

    attachChild(std::move(debris));

    std::cout << "## Asteroid ##" << std::endl;
    std::cout << "\tAngle : " << Angle << std::endl;
    std::cout << "\tSpin: " << Spin << std::endl;
    std::cout << "\tSpeed : " << Speed << std::endl;
    std::cout << "\tScale : " << debrisScale << std::endl;
}

