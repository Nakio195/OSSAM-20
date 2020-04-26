#ifndef BULLET_H
#define BULLET_H

#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Entities/Entity.h"
#include "System/Animation.h"

using namespace std;

class Weapon;
class Spaceship;

class Bullet : public Entity
{
    public:
        enum Type{Laser, Missile};

    public:
        Bullet(Bullet *copy);
        Bullet(Spaceship *pParent, string pName = "Laser Simple", unsigned int pHit = 10, string PathToBulletTexture = "Ressources/Sprite/LaserBleu.png", string PathToBlastTexture = "Ressources/Sprite/missile-blast.png");
        ~Bullet();

        bool isBlastAnimRunning();
        bool isExploded();
        bool NeedRemove(); // To be moved upward in Entity

        unsigned int getType();
        unsigned int getHit();
        void setHit(unsigned int pHit);

        virtual void Move();
        void setDirection(sf::Vector2f pDirection);
        sf::Vector2f getDirection();

        void setSpeed(float pSpeed);
        float getSpeed();

        void setBlastTexture(string Path);
        void setBlastTexture(sf::Texture *pBlast);

        void setBulletTexture(string Path);
        void setBulletTexture(sf::Texture *pBullet);

        void setParent(Spaceship *pParent);
        Spaceship *getParent();
        virtual void draw(sf::RenderWindow *Window);
        void RefreshElapsedTime(bool Release);
        virtual void Hitting(Spaceship *Shooter, Spaceship *Shooted);

        //Actions
        void BlastAnim_EndAction();

    protected:
        unsigned int Type;      // Identifie la sous classe de munition
        unsigned int Hit;       // Dégats en HP/tirs

        sf::Vector2f Direction;

        float Speed; // Vitesse de déplacment en pixels/s
        Spaceship *Parent;

        Animation<Bullet> *BlastAnim;
        sf::Texture *BlastTexture;
        sf::Texture *BulletTexture;
        bool Exploded;
        bool Remove;
};

#endif // BULLET_H
