#ifndef MISSILE_H
#define MISSILE_H

#include "../Bullet.h"

class Spaceship;

class Missile : public Bullet
{
    public:
        Missile(Spaceship *Parent, Spaceship *pTarget = 0);
        Missile(Missile *copy);
        ~Missile();

        virtual void draw(sf::RenderWindow *Window);
        void Move();
        void setTarget(Spaceship* pTarget);
        float getDamageRadius();
        void setDamageRadius(float Radius);
        virtual void Hitting(Spaceship *Shooter, Spaceship *Shooted);

    protected:
        Spaceship *Target;
        float DamageRadius;

};

#endif // MISSILE_H
