#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Entities/Entity.h"
#include "Ressources/RessourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>


class Projectile : public Entity
{
    public:
        enum Type
        {
            LaserBlue,
            LaserRed,
            TypeCount
        };

    public:
        Projectile(Type type, const TextureHolder& textures);

        virtual unsigned int getSceneCategory() const override;
        virtual sf::FloatRect getBoundingRect() const override;

        void kill() override;

        bool isGuided() const;
        float getMaxSpeed() const;
        int getDamage() const;

    private:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        Type mType;
        sf::Sprite mSprite;
        sf::Vector2f mTargetDirection;
};

#endif // PROJECTILE_H
