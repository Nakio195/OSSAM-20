#ifndef DATATABLES_H
#define DATATABLES_H

#include <string>
#include <vector>
#include "Ressources/RessourceIdentifiers.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector3.hpp>
#include "Entities/Projectile.h"
#include "System/Scene/Particle.h"
#include "Items/Weapons/Weapon.h"
#include "System/Animation.h"
#include "Entities/Debris.h"



/** Ideas !!! **/
/**
 * Create a structure for Entity that is integrated inside each inherited type
 */


struct Direction
{
    Direction(float angle, float distance) : angle(angle), distance(distance)
    {
    }

    float angle;
    float distance;
};

struct SpaceShipData
{
    int life;
    int shield;
    float speed;
    float inertia;
    unsigned int attack;
    unsigned int defense;
    unsigned int generator;
    Faction::ID faction;
    Textures::ID texture;

    /** Weapons **/
    Weapon::Type firstWeapon;
    Weapon::Type secondWeapon;
    sf::Time fireInterval;

    /** * Animations **/
    //Explode
    Animation::Type explode_Anim;

    std::vector<Direction> directions;
};

struct WeaponData
{
    std::string name;
    sf::Time fireRate;
    bool needAmmo;
    int ammo;

    Textures::ID texture;
    Icons::ID icon;
    Sounds::ID blastSound;
    std::vector<Weapon::Cannon> cannons;
};

struct ShieldData
{
    std::string name;
    Icons::ID icon;
    int shield;
    sf::Time reloadTime;
    sf::Time cooldownTime;
};

struct ProjectileData
{
    int damage;
    float speed;
    Particle::Type particleType;
    Textures::ID texture;
    sf::Vector2f emitterPosition;
    Animation::Type explode_Anim;
};

struct ParticleData
{
    sf::Color color;
    sf::Time lifetime;
};

struct AnimationData
{
    Textures::ID texture;
    unsigned int frameCount;
    sf::IntRect rect;
    float period;

    Timer::Mode timerMode;
    Animation::Mode mode;

    std::vector<RotationKey> rotationKeys;
    std::vector<TranslationKey> translationKeys;
    std::vector<ScaleKey> scaleKeys;
};

struct DebrisData
{
    Textures::ID texture;
    Debris::Type type;
    float speed;
    int life;

    Sounds::ID explosionSound;
};

struct HudData
{
    Textures::ID background;
};

std::vector<SpaceShipData> initSpaceship();
std::vector<WeaponData> initWeapons();
std::vector<ProjectileData> initProjectiles();
std::vector<ParticleData> initParticleData();
std::vector<AnimationData> initAnimationData();
std::vector<ShieldData> initShields();
std::vector<DebrisData> initDebris();
std::vector<HudData> initHud();

#endif // DATATABLES_H
