#include "Debris.h"
#include "DataTables.h"

namespace
{
    const std::vector<DebrisData> Table = initDebris();
}


Debris::Debris(Debris::Type type, const TextureHolder& textures) : Entity(Table[type].life),
    mSprite(textures.get(Table[type].texture)),
    mExplodeSound(Table[type].explosionSound)
{
    setSpeed(Table[type].speed);
    mSize = 0;
}

void Debris::updateCurrent(sf::Time dt, CommandQueue &Commands)
{
    if(!isDying())
    {
        //accelerate(getVelocity());
        mSprite.rotate(mRotation*dt.asSeconds());
        Entity::updateCurrent(dt, Commands);
    }

    else
        destroy();
}

void Debris::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
    Entity::drawForces(target, states);
}

void Debris::setSpin(float spin)
{
    mRotation = spin;
}

float Debris::getSpin() const
{
    return mRotation;
}

sf::FloatRect Debris::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

unsigned int Debris::getSceneCategory() const
{
    return Category::Debris;
}

void Debris::kill()
{
    if(mSize == 0)
        Entity::kill();
}
