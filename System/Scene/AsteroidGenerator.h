#ifndef GENERATORNODE_H
#define GENERATORNODE_H

#include <random>

#include "System/Scene/SceneNode.h"
#include "Ressources/RessourceIdentifiers.h"
#include "System/Timer.h"
#include "System/Utilities.h"

#include "Entities/Debris.h"

class AsteroidGenerator : public SceneNode
{
    public:

    public:
        AsteroidGenerator(const TextureHolder& textures);

        void start();
        void pause(bool paused = true);
        void resume();
        void stop();

        virtual void trigger(sf::Time dt, CommandQueue &Commands);

        randomFloat frequency;
        randomFloat spin;
        randomFloat angle;
        randomFloat speed;
        randomFloat scale;

        virtual void updateCurrent(sf::Time dt, CommandQueue &Commands) override;

        virtual unsigned int getSceneCategory() const override;
        virtual sf::FloatRect getBoundingRect() const override;

    private:
        const TextureHolder& mTextures;
        Timer mTimer;
};

#endif // GENERATORNODE_H
