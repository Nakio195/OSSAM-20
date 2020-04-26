#include "DataTables.h"
#include <vector>

#include "Entities/Spaceship.h"
#include "System/Scene/ParticleNode.h"
#include "Items/Weapons/Weapon.h"
#include "Items/Shield.h"

std::vector<SpaceShipData> initSpaceship()
{
    std::vector<SpaceShipData> data(Spaceship::TypeCount);

    data[Spaceship::Khaal].life = 100;
    data[Spaceship::Khaal].speed = 300.f;
    data[Spaceship::Khaal].inertia = 0.95f;
    data[Spaceship::Khaal].shield = 200.f;
    data[Spaceship::Khaal].generator = 10;
    data[Spaceship::Khaal].attack = 10;
    data[Spaceship::Khaal].defense = 10;
    data[Spaceship::Khaal].faction = Faction::Player;
    data[Spaceship::Khaal].firstWeapon = Weapon::Laser1;
    data[Spaceship::Khaal].secondWeapon = Weapon::Laser2;
    data[Spaceship::Khaal].texture = Textures::Khaal;
    data[Spaceship::Khaal].explode_Anim = Animation::Khaal_Explode;

    data[Spaceship::Intercepter].life = 20;
    data[Spaceship::Intercepter].speed = 80.f;
    data[Spaceship::Intercepter].inertia = 0.5f;
    data[Spaceship::Intercepter].shield = 200.f;
    data[Spaceship::Intercepter].generator = 10;
    data[Spaceship::Intercepter].attack = 10;
    data[Spaceship::Intercepter].defense = 10;
    data[Spaceship::Intercepter].faction = Faction::WASP;
    data[Spaceship::Intercepter].firstWeapon = Weapon::Laser1;
    data[Spaceship::Intercepter].secondWeapon = Weapon::Laser2;
    data[Spaceship::Intercepter].texture = Textures::Intercepter;
    data[Spaceship::Intercepter].explode_Anim = Animation::Classic_Explode;

    data[Spaceship::Blade].life = 40;
    data[Spaceship::Blade].speed = 50.f;
    data[Spaceship::Blade].inertia = 0.5f;
    data[Spaceship::Blade].shield = 200.f;
    data[Spaceship::Blade].generator = 10;
    data[Spaceship::Blade].attack = 10;
    data[Spaceship::Blade].defense = 10;
    data[Spaceship::Blade].faction = Faction::WASP;
    data[Spaceship::Blade].firstWeapon = Weapon::Laser3;
    data[Spaceship::Blade].secondWeapon = Weapon::Laser3;
    data[Spaceship::Blade].texture = Textures::Blade;
    data[Spaceship::Blade].explode_Anim = Animation::Classic_Explode;

    return data;
}

std::vector<WeaponData> initWeapons()
{
    std::vector<WeaponData> data(Weapon::WeaponsCount);

    data[Weapon::Laser1].name = std::string("Canon laser fatigué");
    data[Weapon::Laser1].needAmmo = false;
    data[Weapon::Laser1].ammo = -1;
    data[Weapon::Laser1].texture = Textures::LaserGun;
    data[Weapon::Laser1].blastSound = Sounds::CP_Blast;
    data[Weapon::Laser1].icon = Icons::Laser1;
    data[Weapon::Laser1].fireRate = sf::seconds(0.4f);
    data[Weapon::Laser1].cannons.push_back(Weapon::Cannon(sf::Vector2f(87.f, 6.f), 0.f, Projectile::LaserBlue, Animation::LaserBlue_Fire));

    data[Weapon::Laser2].name = std::string("Double canon laser");
    data[Weapon::Laser2].needAmmo = false;
    data[Weapon::Laser2].ammo = -1;
    data[Weapon::Laser2].texture = Textures::LaserGun;
    data[Weapon::Laser2].icon = Icons::Laser2;
    data[Weapon::Laser2].blastSound = Sounds::CP_Blast;
    data[Weapon::Laser2].fireRate = sf::seconds(0.6f);
    data[Weapon::Laser2].cannons.push_back(Weapon::Cannon(sf::Vector2f(87.f, 3.f), -30.f, Projectile::LaserRed, Animation::LaserBlue_Fire));
    data[Weapon::Laser2].cannons.push_back(Weapon::Cannon(sf::Vector2f(87.f, 9.f), 30.f, Projectile::LaserRed, Animation::LaserBlue_Fire));

    data[Weapon::Laser3].name = std::string("Triple canon laser");
    data[Weapon::Laser3].needAmmo = false;
    data[Weapon::Laser3].ammo = -1;
    data[Weapon::Laser3].texture = Textures::LaserGun;
    data[Weapon::Laser3].blastSound = Sounds::CP_Blast;
    data[Weapon::Laser3].icon = Icons::Laser3;
    data[Weapon::Laser3].fireRate = sf::seconds(0.8f);
    data[Weapon::Laser3].cannons.push_back(Weapon::Cannon(sf::Vector2f(87.f, 3.f), -15.f, Projectile::LaserBlue, Animation::LaserBlue_Fire));
    data[Weapon::Laser3].cannons.push_back(Weapon::Cannon(sf::Vector2f(87.f, 6.f), 0.f, Projectile::LaserRed, Animation::LaserBlue_Fire));
    data[Weapon::Laser3].cannons.push_back(Weapon::Cannon(sf::Vector2f(87.f, 9.f), 15.f, Projectile::LaserBlue, Animation::LaserBlue_Fire));

    return data;
}

std::vector<ShieldData> initShields()
{
    std::vector<ShieldData> data(Shield::ShieldCount);

    data[Shield::Pouclier].name = std::string("Pouclier");
    data[Shield::Pouclier].icon = Icons::Pouclier;
    data[Shield::Pouclier].shield = 10;
    data[Shield::Pouclier].reloadTime = sf::seconds(2);
    data[Shield::Pouclier].cooldownTime = sf::seconds(2);
    return data;
}

std::vector<ProjectileData> initProjectiles()
{
    std::vector<ProjectileData> data(Projectile::TypeCount);

    data[Projectile::LaserRed].damage = 20;
    data[Projectile::LaserRed].speed = 800.f;
    data[Projectile::LaserRed].particleType = Particle::RedSmoke;
    data[Projectile::LaserRed].emitterPosition = sf::Vector2f(20.f, 0.f);
    data[Projectile::LaserRed].texture = Textures::LaserRed;

    data[Projectile::LaserBlue].damage = 5;
    data[Projectile::LaserBlue].speed = 800.f;
    data[Projectile::LaserBlue].particleType = Particle::BlueSmoke;
    data[Projectile::LaserBlue].emitterPosition = sf::Vector2f(20.f, 0.f);
    data[Projectile::LaserBlue].texture = Textures::LaserBlue;

    return data;
}

std::vector<AnimationData> initAnimationData()
{
    std::vector<AnimationData> data(Animation::AnimationsCount);

    data[Animation::Khaal_Explode].texture = Textures::Khaal_Explode;
    data[Animation::Khaal_Explode].period = 0.15f;
    data[Animation::Khaal_Explode].timerMode = Timer::OneShot;
    data[Animation::Khaal_Explode].frameCount = 4;
    data[Animation::Khaal_Explode].rect = sf::IntRect(0, 0, 177, 153);
    data[Animation::Khaal_Explode].mode = Animation::Sprite;

    data[Animation::Classic_Explode].texture = Textures::Classic_Explode;
    data[Animation::Classic_Explode].period = 0.15f;
    data[Animation::Classic_Explode].timerMode = Timer::OneShot;
    data[Animation::Classic_Explode].frameCount = 3u;
    data[Animation::Classic_Explode].rect = sf::IntRect(0, 0, 130, 140);
    data[Animation::Classic_Explode].mode = Animation::Sprite;

    data[Animation::LaserBlue_Fire].texture = Textures::LaserBlue_Fire;
    data[Animation::LaserBlue_Fire].period = 0.10f;
    data[Animation::LaserBlue_Fire].timerMode = Timer::OneShot;
    data[Animation::LaserBlue_Fire].frameCount = 2u;
    data[Animation::LaserBlue_Fire].rect = sf::IntRect(0, 0, 40, 24);
    data[Animation::LaserBlue_Fire].mode = Animation::Sprite;

    data[Animation::Planet1].texture = Textures::Planet1;
    data[Animation::Planet1].period = 0.f;
    data[Animation::Planet1].timerMode = Timer::Continuous;
    data[Animation::Planet1].frameCount = 1u;
    data[Animation::Planet1].rect = sf::IntRect(0, 0, 525, 533);
    data[Animation::Planet1].mode = Animation::KeySequence;
    data[Animation::Planet1].rotationKeys.push_back(RotationKey(360, true, 360.f));
    return data;
}

std::vector<ParticleData> initParticleData()
{
    std::vector<ParticleData> data(Particle::ParticleCount);

    data[Particle::RedSmoke].color = sf::Color(255, 162, 162);
    data[Particle::RedSmoke].lifetime = sf::seconds(0.6f);

    data[Particle::BlueSmoke].color = sf::Color(162, 255, 255);
    data[Particle::BlueSmoke].lifetime = sf::seconds(0.2f);

    return data;
}

std::vector<DebrisData> initDebris()
{
    std::vector<DebrisData> data(Debris::DebrisCount);

    data[Debris::Spaceship].life = 20;
    data[Debris::Spaceship].speed = 200;
    data[Debris::Spaceship].texture = Textures::SpaceshipDebris;
    data[Debris::Spaceship].explosionSound = Sounds::ClassicExplode;

    data[Debris::Asteroid].life = 100;
    data[Debris::Asteroid].speed = 50;
    data[Debris::Asteroid].texture = Textures::AsteroidDebris;
    data[Debris::Asteroid].explosionSound = Sounds::ClassicExplode;

    return data;

}

