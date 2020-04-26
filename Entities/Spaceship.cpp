#include "Entities/Spaceship.h"

#include "Ressources/RessourceHolder.h"
#include "Entities/DataTables.h"
#include "System/Utilities.h"
#include <math.h>
#include <iostream>

namespace
{
    const std::vector<SpaceShipData> Table = initSpaceship();
}


Spaceship::Spaceship(Type type, const TextureHolder& textures, const FontHolder& fonts, const IconHolder& icons) :
    Entity(Table[type].life),
    mType(type),
    mSprite(textures.get(Table[type].texture)),
    mExplodeAnim(Table[type].explode_Anim, textures)
{
    centerOrigin(mSprite);
    setFaction(Table[type].faction);
    setInertia(Table[type].inertia);
    setSpeed(Table[type].speed);

    std::unique_ptr<Weapon> firstWeapon(new Weapon(Table[type].firstWeapon, textures, icons));
    firstWeapon->setOwner(this);
    firstWeapon->setFaction(Table[type].faction);
    mMainWeapon = firstWeapon.get();
    this->attachChild(std::move(firstWeapon));

    std::unique_ptr<Weapon> secondWeapon(new Weapon(Table[type].secondWeapon, textures, icons));
    secondWeapon->setOwner(this);
    secondWeapon->setFaction(Table[type].faction);
    mSecondaryWeapon = secondWeapon.get();
    this->attachChild(std::move(secondWeapon));

    mMainWeapon->setState(Item::Equiped);
    mSecondaryWeapon->setState(Item::Equiped);

    if(!isAllied())
    {
        mMainWeapon->rotate(180.f);
        mSecondaryWeapon->rotate(180.f);
    }

    mStats = getMaxStats();

    std::unique_ptr<TextNode> LifeText(new TextNode(fonts, ""));
    mLifeText = LifeText.get();
    attachChild(std::move(LifeText));

    // Explode Animation
    Command destroyOnExplode;
    destroyOnExplode.category = Category::Spaceship;
    destroyOnExplode.action = derivedAction<Spaceship> ([this] (SceneNode&, sf::Time)
    {
        this->destroy();
    });
    mExplodeAnim.setEndAction(destroyOnExplode);

}

void Spaceship::updateCurrent(sf::Time dt, CommandQueue& Commands)
{
    if(mNeedRemove)
        return;

    if(!isDying())
    {
        Entity::updateCurrent(dt, Commands);
        mLifeText->setString(toString(getStats().life) + " HP");
        mLifeText->setPosition(0.f, 50.f);
        mLifeText->setRotation(-getRotation());

        if(!isAllied())
            shoot(Weapon::Main);
    }

    else
    {
        if(!mExplodeAnim.isRunning())
        {
            mExplodeAnim.start();
            playSound(Sounds::ClassicExplode, Commands);
        }

        else
            mExplodeAnim.play(dt, Commands);
    }


}

void Spaceship::kill()
{
    Entity::kill();
    mStats.life = 0;
    mLifeText->setString("");

    mMainWeapon->kill();
    mSecondaryWeapon->kill();
}

void Spaceship::updateAutoMove(sf::Time dt)
{

}

void Spaceship::shoot(Weapon::Select select)
{
    switch (select)
    {
        case Weapon::Main:
            mMainWeapon->shoot();
            break;

        case Weapon::Secondary:
            mSecondaryWeapon->shoot();
            break;
    }
}


const Spaceship::Statistics Spaceship::getStats() const
{
    return mStats;
}

Spaceship::Statistics Spaceship::getMaxStats() const
{
    Statistics stats;
    stats.life = Table[mType].life;
    stats.speed = Table[mType].speed;
    stats.inertia = Table[mType].inertia;
    stats.attack = Table[mType].attack;
    stats.shield = Table[mType].shield;
    stats.defense = Table[mType].defense;
    stats.generator = Table[mType].generator;

    return stats;
}

void Spaceship::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(!isDying())
        target.draw(mSprite, states);
    else
        target.draw(mExplodeAnim, states);

    Entity::drawForces(target, states);
}

bool Spaceship::isAllied() const
{
    if(getSceneCategory() & (Category::PlayerSpaceship|Category::AlliedSpaceship))
        return true;
    else
        return false;
}

unsigned int Spaceship::getSceneCategory() const
{
    switch(mType)
    {
        case Type::Khaal:
            return Category::PlayerSpaceship|Category::AlliedSpaceship;

        case Type::Intercepter:
        case Type::Blade:
            return Category::EnemySpaceship;

        default:
            return Category::None;
    }
}

void Spaceship::takeDamage(const int damage)
{
    mStats.life -= damage;

    if(mStats.life <= 0)
        kill();
}

void Spaceship::takeDamage(const Projectile& projectile)
{
    mStats.life -= projectile.getDamage();

    if(mStats.life <= 0)
        kill();
}

bool Spaceship::isPlayer() const
{
    if(mType == Spaceship::Khaal)
        return true;
    else
        return false;
}

sf::FloatRect Spaceship::getBoundingRect() const
{
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

