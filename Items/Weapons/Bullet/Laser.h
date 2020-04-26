#ifndef LASER_H
#define LASER_H

#include "../Bullet.h"

class Spaceship;

class Laser : public Bullet
{
    public:
        Laser(Spaceship *Parent);
        Laser(Laser *copy);
        ~Laser();

        virtual void Move();

        virtual void Hitting(Spaceship *Shooter, Spaceship *Shooted);
};

#endif // LASER_H
