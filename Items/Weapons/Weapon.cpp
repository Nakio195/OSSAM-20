#include "Weapon.h"
#include <iostream>

#include "Entities/DataTables.h"
#include "Ressources/RessourceHolder.h"
#include "System/Utilities.h"

namespace
{
    const std::vector<WeaponData> Table = initWeapons();
}


Weapon::Weapon(Weapon::Type type, const TextureHolder& textures, const IconHolder& icons) :
    Item(Table[type].name, icons, Table[type].icon),
    Entity(textures)
{
    SceneNode::mDefaultCategory = Category::Weapon;
    mType = type;
    Item::setType(Item::Weapon);

    mBlastSound = Table[type].blastSound;

    setFireRate(Table[type].fireRate);
    mNeedAmmo = Table[type].needAmmo;
    mAmmo = Table[type].ammo;
    mCannons = Table[type].cannons;

    for(auto& cannon : mCannons)
    {
        Animation blast(cannon.blast_Anim, textures);
        blast.setPosition(cannon.position);
        blast.setRotation(cannon.angle);
        mBlastAnims.push_back(blast);
    }

    mFire = false;

    mReloadTimer.setPeriod(mFireRate);
    mReloadTimer.setMode(Timer::OneShot);

    mSprite.setTexture(textures.get(Table[mType].texture));

    mFireCommand.category = Category::SceneProjectileLayer;
    mFireCommand.action = [this, &textures] (SceneNode& node, sf::Time)
    {
        this->launch(node, textures);
    };

}

void Weapon::updateCurrent(sf::Time dt, CommandQueue &Commands)
{
    Entity::updateCurrent(dt, Commands);

    mReloadTimer.Count(dt);

    for(auto& blast : mBlastAnims)
    {
        if(blast.isRunning())
            blast.play(dt, Commands);
    }

    if(mFire)
    {
        mFire = false;
        Commands.push(mFireCommand);
        playSound(mBlastSound, Commands);
    }
}


void Weapon::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(!isDying())
    {
        target.draw(mSprite, states);

        for(auto& blast : mBlastAnims)
        {
            target.draw(blast, states);
        }
    }
}

unsigned int Weapon::getSceneCategory() const
{
    return Category::Weapon;
}

bool Weapon::shoot()
{
    if(getState() != Item::Equiped)
        return false;

    if(mReloadTimer.Triggered())
        mReloadTimer.StopTimer();

    if(!mReloadTimer.isRunning())
    {
        if(mNeedAmmo)
        {
            if(mAmmo > 0)
                mAmmo--;
            else
                return false;
        }

        mReloadTimer.StartTimer();

        for(auto& blast : mBlastAnims)
            blast.start();

        mFire = true;

        return true;
    }

    else
    {
        return false;
    }
}


void Weapon::launch(SceneNode& parent, const TextureHolder& textures)
{
    sf::Vector2f mPosition = this->getWorldPosition();

    for(auto& cannon : mCannons)
    {
        std::unique_ptr<Projectile> projectile(new Projectile(cannon.projectile, textures));

        sf::Vector2f Velocity = fromAngle(cannon.angle + this->getRotation()) * projectile->getMaxSpeed();

        projectile->setPosition(sf::Vector2f(cannon.position.x, cannon.position.y) + mPosition);
        projectile->setRotation(cannon.angle + this->getRotation());
        projectile->applyForce(Velocity, Force::Constant);
        projectile->setFaction(getFaction());
        parent.attachChild(std::move(projectile));
    }
}


sf::Time Weapon::getFireRate()
{
    return mFireRate;
}

void Weapon::setFireRate(sf::Time fireRate)
{
    mFireRate = fireRate;
    mReloadTimer.setPeriod(mFireRate);
}
