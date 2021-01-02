#include "Debris.h"
#include "DataTables.h"

#include "System/Utilities.h"

namespace
{
    const std::vector<DebrisData> Table = initDebris();
}


Debris::Debris(Debris::Type type, const TextureHolder& textures) : Entity(textures, Table[type].life),
    mSprite(textures.get(Table[type].texture)),
    mExplodeSound(Table[type].explosionSound)
{
    centerOrigin(mSprite);
    setSpeed(Table[type].speed);
    mSize = 0;
}

void Debris::updateCurrent(sf::Time dt, CommandQueue &Commands)
{
    Entity::updateCurrent(dt, Commands);

    if(!isDying())
    {
        mSprite.rotate(mRotation*dt.asSeconds());
    }

}

void Debris::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(!isDying())
        target.draw(mSprite, states);
    else
        target.draw(mDyingAnim, states);
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
