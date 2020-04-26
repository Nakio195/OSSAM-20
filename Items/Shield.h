#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"
#include "System/Timer.h"
#include "Entities/Projectile.h"

class Entity;

class Shield : public Item
{
    public:
        enum Type{Pouclier, ShieldCount};

    public:
        Shield(Shield::Type, const TextureHolder& textures, const IconHolder& icons);
        int TakeDamage(const Projectile& Damage);
        int getShieldPoints();
        int getShieldMax();
        void RefreshElapsedTime(bool Release = false);

        sf::Vector2f getRelativePosition();
        void setShieldTexture(sf::Texture *Texture);
        void setShieldTexture(std::string PathShield, std::string PathBroken = "");
        void draw(sf::RenderWindow *Window);

    private:        
        int mShieldMax;
        int mShieldPoints;
        Timer ReloadTimer;
        Timer CooldownTimer;

        Entity *Parent;
        sf::Sprite MainSprite;
        sf::Texture *Texture_Shield;
        sf::Texture *Texture_Broken;
        sf::Vector2f RelativePosition;

        bool Hitted;
        bool Broken;
        Timer Hitmark;

};

#endif // SHIELD_H
