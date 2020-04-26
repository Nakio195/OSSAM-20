#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "Ressources/RessourceIdentifiers.h"
#include "Entities/Entity.h"
#include "Items/Item.h"
#include "Entities/Projectile.h"
#include "System/Timer.h"
#include "System/Animation.h"

class Weapon : public Item, public Entity
{
    public:
        enum Select{Main, Secondary};
        enum Type{Laser1, Laser2, Laser3, Missile, WeaponsCount};

    public:
        Weapon(Weapon::Type, const TextureHolder& textures, const IconHolder& icons);

        // Parents method overload
        virtual void updateCurrent(sf::Time dt, CommandQueue &) override;
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual unsigned int getSceneCategory() const override;

        void setProjectile(Projectile::Type type);
        virtual bool shoot();

        sf::Time getFireRate();
        void setFireRate(sf::Time pSpeed);

    public:
        struct Cannon
        {
            Cannon(sf::Vector2f position, float angle, Projectile::Type projectile, Animation::Type blast) :
                position(position),
                angle(angle),
                projectile(projectile),
                blast_Anim(blast)
            {
            }

            sf::Vector2f position;
            float angle;
            Projectile::Type projectile;
            Animation::Type blast_Anim;
        };

    private:
        void launch(SceneNode& parent, const TextureHolder& textures);

    private:
        Weapon::Type mType;

        sf::Time  mFireRate;        //Cadence de tir en tir/s
        std::vector<Cannon> mCannons; // x, y , theta

        bool mNeedAmmo;
        int mAmmo;

        Command mFireCommand;

        bool mFire;
        Timer mReloadTimer;
        sf::Sprite mSprite;
        Sounds::ID mBlastSound;

        //Textures et anim
        std::vector<Animation> mBlastAnims;

};

#endif // WEAPON_H
