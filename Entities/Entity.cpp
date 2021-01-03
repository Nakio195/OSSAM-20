#include "Entities/Entity.h"
#include "System/Scene/SoundNode.h"
#include "System/Utilities.h"

using namespace std::placeholders;

Entity::Entity(const TextureHolder& textures, int HealthPoints, Animation::Type type) : SceneNode(), mDyingAnim(type, textures)
{
    mHealthPoints = HealthPoints;
    mFaction = Faction::None;
    mDead = false;
    mDying = false;
    mAcceleration = 0.f;
    mInertia = 1.f;
    mSpeed = 100.f;

    Command destroyOnExplode;
    destroyOnExplode.category = Category::Entity;
    destroyOnExplode.action = derivedAction<Entity> ([this] (SceneNode&, sf::Time)
    {
        this->destroy();
    });
    mDyingAnim.setEndAction(destroyOnExplode);
}

void Entity::setInertia(float inertia)
{
    mInertia = inertia;
}

float Entity::getInertia()
{
    return mInertia;
}

void Entity::setSpeed(float speed)
{
    mSpeed = speed;
}

float Entity::getSpeed()
{
    return mSpeed;
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float x, float y)
{
    mVelocity.x = x;
    mVelocity.y = y;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}

void Entity::setAcceleration(float acceleration)
{
    mAcceleration = acceleration;
}

float Entity::getAcceleration()
{
    return mAcceleration;
}

void Entity::accelerate(sf::Vector2f velocity)
{
    applyForce(velocity);
}

void Entity::accelerate(float x, float y)
{
    applyForce(sf::Vector2f(x, y));
}

void Entity::setFaction(Faction::ID faction)
{
    mFaction = faction;
}

Faction::ID Entity::getFaction() const
{
    return mFaction;
}

int Entity::getHealthPoints() const
{
    return mHealthPoints;
}

void Entity::takeDamage(int damages)
{
    if(mHealthPoints - damages < 0)
        kill();

    mHealthPoints = mHealthPoints - damages;
}

void Entity::takeRepair(int repair)
{
   mHealthPoints = mHealthPoints + repair;
}

void Entity::playSound(Sounds::ID effect, CommandQueue& Commands)
{
    Command command;
    command.category = Category::SoundNode;
    command.action = derivedAction<SoundNode>(std::bind(&SoundNode::playSound, _1, effect, getWorldPosition()));

    Commands.push(command);
}

bool Entity::isDying() const
{
    return mDying;
}

bool Entity::isDead() const
{
    return mDead;
}

void Entity::kill()
{
    mDying = true;
}

void Entity::applyForce(sf::Vector2f force, Force::Type type, sf::Time duration)
{
    Force f;
    f.force = force;
    f.type = type;
    f.duration = duration;

    mForces.push_back(f);
}

void Entity::applyForce(Force f)
{
    mForces.push_back(f);
}

void Entity::updateForces(sf::Time dt)
{
    sf::Vector2f result(0.f, 0.f);
    unsigned int count = 0;

    for(auto& force : mForces)
    {
        if(force.type != Force::Finished)
        {
            result = result + force.force;
            count++;
        }

        force.update(dt);
    }

    mForces.remove_if([] (const Force& force) {return force.type == Force::Finished;});
    mDirection = result;

}

void Entity::updateCurrent(sf::Time dt, CommandQueue& Commands)
{
    if(!isDying())
    {
        updateForces(dt);

        if(mAcceleration != 0.f)
            mVelocity = mDirection * mAcceleration*dt.asSeconds();
        else
            mVelocity = mDirection;

        mVelocity = saturateVector(mVelocity, mSpeed);
        move(mVelocity*dt.asSeconds());
    }

    else
    {
        if(!mDyingAnim.isRunning())
        {
            mDyingAnim.start();
            playSound(Sounds::ClassicExplode, Commands);
        }

        else
            mDyingAnim.play(dt, Commands);
    }
}

void Entity::drawForces(sf::RenderTarget &target, sf::RenderStates &) const
{
    for(auto& force : mForces)
    {
        sf::RectangleShape rect(sf::Vector2f(length(force.force/2.f), 2));
        rect.setFillColor(sf::Color::Cyan);
        rect.setOrigin(0, 0);
        rect.setPosition(getWorldPosition());
        rect.setRotation(getAngle(force.force)-90);
        target.draw(rect);
    }

    sf::RectangleShape rect(sf::Vector2f(length(getVelocity()/2.f), 2));
    rect.setFillColor(sf::Color::Blue);
    rect.setOrigin(0, 0);
    rect.setPosition(getWorldPosition());
    rect.setRotation(getAngle(getVelocity())-90);
    target.draw(rect);
}


