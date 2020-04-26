#include "EmitterNode.h"

#include "System/Scene/ParticleNode.h"
#include "System/Commands/Command.h"

EmitterNode::EmitterNode(Particle::Type type) : SceneNode(Category::Emitter), mAcumulatedTime(sf::Time::Zero), mType(type), mParticleSystem(nullptr)
{
    mDefaultCategory = Category::Emitter;
}

void EmitterNode::updateCurrent(sf::Time dt, CommandQueue &Commands)
{
    if(mParticleSystem)
        emitParticles(dt);
    else
    {
        auto finder = [this] (ParticleNode& container, sf::Time)
        {
            if(container.getParticleType() == mType)
                mParticleSystem = &container;
        };

        Command command;
        command.category = Category::Particle;
        command.action = derivedAction<ParticleNode>(finder);

        Commands.push(command);
    }
}

void EmitterNode::emitParticles(sf::Time dt)
{
    const float emissionRate = 100.f;
    const sf::Time interval = sf::seconds(1.f) / emissionRate;

    mAcumulatedTime += dt;

    while(mAcumulatedTime > interval)
    {
        mAcumulatedTime -= interval;
        mParticleSystem->addParticle(getWorldPosition());
    }
}

