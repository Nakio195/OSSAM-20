#ifndef EMITTERNODE_H
#define EMITTERNODE_H

#include "System/Scene/Particle.h"
#include "System/Scene/SceneNode.h"

class ParticleNode;

class EmitterNode : public SceneNode
{
    public:
        EmitterNode(Particle::Type type);

        virtual void updateCurrent(sf::Time dt, CommandQueue &Commands);

        void emitParticles(sf::Time dt);

    private:
        sf::Time mAcumulatedTime;
        Particle::Type mType;
        ParticleNode* mParticleSystem;
};

#endif // EMITTERNODE_H
