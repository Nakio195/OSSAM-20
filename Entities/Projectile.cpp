#include "Projectile.h"

#include "Entities/DataTables.h"
#include "System/Utilities.h"
#include "Ressources/RessourceHolder.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "System/Scene/EmitterNode.h"

#include <cmath>
#include <cassert>


namespace
{
    const std::vector<ProjectileData> Table = initProjectiles();
}

Projectile::Projectile(Type type, const TextureHolder& textures) : Entity(1), mType(type), mSprite(textures.get(Table[type].texture)), mTargetDirection()
{
    centerOrigin(mSprite);
    setAcceleration(0.f);
    setSpeed(Table[type].speed);

    mDefaultCategory = getSceneCategory();

    std::unique_ptr<EmitterNode> smoke(new EmitterNode(Table[type].particleType));
    smoke->setPosition(Table[type].emitterPosition);
    attachChild(std::move(smoke));
}

bool Projectile::isGuided() const
{
    return false;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
   if(isDying())
       destroy();

    Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

unsigned int Projectile::getSceneCategory() const
{
    if (getFaction() == Faction::WASP)
        return Category::EnemyProjectile;
    else
        return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const
{
    return Table[mType].speed;
}

int Projectile::getDamage() const
{
    return Table[mType].damage;
}
