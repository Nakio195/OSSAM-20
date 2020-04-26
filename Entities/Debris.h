#ifndef DEBRIS_H
#define DEBRIS_H

#include <SFML/Graphics/Sprite.hpp>

#include "Entities/Entity.h"
#include "Ressources/RessourceHolder.h"
#include "System/SoundPlayer.h"

class Debris : public Entity
{
    public:
        enum Type{
            Asteroid,
            Spaceship,
            DebrisCount
        };

    public:
        Debris(Debris::Type type, const TextureHolder& textures);

        void setSpin(float spin);
        float getSpin() const;

        virtual void kill() override;

        virtual void updateCurrent(sf::Time dt, CommandQueue &Commands) override;
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

        sf::FloatRect getBoundingRect() const override;
        virtual unsigned int getSceneCategory() const override;

    private:
        sf::Sprite mSprite;
        float mRotation;

        unsigned int mSize;

        Sounds::ID mExplodeSound;

};

#endif // DEBRIS_H
