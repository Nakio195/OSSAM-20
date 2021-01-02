#ifndef ENTITY_H
#define ENTITY_H

#include <list>
#include <SFML/Graphics.hpp>
#include "System/Scene/SceneNode.h"
#include "Ressources/RessourceIdentifiers.h"

#include "System/Animation.h"

namespace Faction
{
    enum ID
    {
        None            = 0,
        Player          = 1 << 1,
        WASP            = 1 << 2,
        FactionCount    = 2
    };
};

struct Force
{
    Force() : type(Force::Constant), force(sf::Vector2f()), duration(sf::Time::Zero)
    {}

    enum Type{Finished, Constant, Impulse};

    void update(sf::Time dt)
    {
        duration -= dt;

        if(duration.asSeconds() <= 0.f && type == Type::Impulse)
            type = Type::Finished;
    }

    Force::Type type;
    sf::Vector2f force;
    sf::Time duration;
};

class Entity : public SceneNode
{
    public:
        Entity(const TextureHolder& textures, int HealthPoints = 1, Animation::Type type = Animation::Type::Classic_Explode);

        virtual void updateCurrent(sf::Time dt, CommandQueue&Commands) override;

        /** GamePlay **/
        void setFaction(Faction::ID faction);
        Faction::ID getFaction() const;
        int getHealthPoints() const;

        virtual bool isDying() const;
        virtual bool isDead() const override;
        virtual void kill();

        virtual void takeDamage(int damages);
        virtual void takeRepair(int repair);

        /** Physic **/
        void setAcceleration(float acceleration);
        float getAcceleration();
        void setSpeed(float speed);
        float getSpeed();
        sf::Vector2f getVelocity() const;
        void setMass(float mass);
        float getMass();
        void setInertia(float inertia);
        float getInertia();
        void accelerate(sf::Vector2f velocity);
        void accelerate(float x, float y);

        void applyForce(sf::Vector2f force, Force::Type type = Force::Impulse, sf::Time duration = sf::Time::Zero);
        void applyForce(Force newForce);
        void updateForces(sf::Time dt);


        /** Sound **/
        void playSound(Sounds::ID effect, CommandQueue& Commands);

        /** visual Debug **/
        void drawForces(sf::RenderTarget &target, sf::RenderStates &) const;

    protected:
        /** My animations **/
        Animation mDyingAnim;

    private:
        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float x, float y);

        /** My stats **/
        int mHealthPoints;
        bool mDead;
        bool mDying;
        Faction::ID mFaction;

        /** My physic **/
        std::list<Force> mForces;
        sf::Vector2f mVelocity;
        sf::Vector2f mDirection;
        float mAcceleration;
        float mInertia;
        float mSpeed;



};

#endif // ENTITY_H
