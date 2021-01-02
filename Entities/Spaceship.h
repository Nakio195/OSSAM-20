#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <SFML/Graphics.hpp>
#include "System/Commands/Category.h"
#include "Entities/Entity.h"
#include "Ressources/RessourceIdentifiers.h"
#include "System/Scene/TextNode.h"
#include "System/Inventory.h"
#include "System/Animation.h"

class Inventory;
class Item;
class ATH;

class Spaceship : public Entity
{
    public:
        enum Type{Khaal, Intercepter, Blade, TypeCount};

        struct Statistics
        {
            /** Common caracteristics **/
            int life;
            int shield;
            float speed;
            float inertia;
            unsigned int generator;
            unsigned int attack;
            unsigned int defense;
        };

    public:
        Spaceship(Type type, const TextureHolder& textures, const FontHolder& fonts, const IconHolder &icons);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void updateCurrent(sf::Time dt, CommandQueue& Commands) override;

        virtual void kill() override;

        sf::FloatRect getBoundingRect() const override;
        virtual unsigned int getSceneCategory() const override;

        void updateAutoMove(sf::Time dt);

        const Statistics getStats() const;
        Spaceship::Statistics getMaxStats() const;
        Inventory& getInventory() const;
        bool addItem(Item& newItem);
        void shoot(Weapon::Select select);

        virtual void takeDamage(const int damage) override;
        void takeDamage(const Projectile& projectile);
        bool isPlayer() const;
        bool isAllied() const;

        void setAimedTarget(Spaceship* pTarget);
        Spaceship* getAimedTarget();
        void setAimed(bool pAimed);

        ATH& getUI();

    private:
        Type mType;
        sf::Sprite mSprite;
        Statistics mStats;

        /** ATH **/
        TextNode* mLifeText;

        /** AutoMove **/
        float mTravelledDistance;
        std::size_t mDirectionIndex;

        /** Weapons and Fire **/
        Weapon *mMainWeapon;
        Weapon *mSecondaryWeapon;

        /** Graphics and animations **/


};


#endif
