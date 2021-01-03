#include "World.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include "System/Scene/ParticleNode.h"
#include "System/Scene/SoundNode.h"
#include "System/Scene/AnimationNode.h"
#include "System/Scene/AsteroidGenerator.h"
#include "System/Utilities.h"

World::World(sf::RenderWindow& window, SoundPlayer& sounds) : mWindow(window), mSounds(sounds), mTextures(), mFonts(), mSceneGraph(), mSceneLayers()
{
    mWorldBounds = sf::FloatRect(0.f, 0.f, 8000.f, mWorldView.getSize().y);
    mSpawnPosition = sf::Vector2f(mWorldView.getSize().x /4.f, mWorldView.getSize().y / 2.f);

    mWorldView = window.getDefaultView();
    mBackgroundView = window.getDefaultView();
    mBackground2View = window.getDefaultView();

    mWorldView.setCenter(mWorldView.getSize().x/2, mWorldView.getCenter().y);
    mBackgroundView.setCenter(mWorldView.getSize().x/2, mBackgroundView.getCenter().y);
    mBackground2View.setCenter(mWorldView.getSize().x/2, mBackground2View.getCenter().y);

    mPlayerSpaceship = nullptr;
    mViewLocked = false;

    loadTextures();
    loadFonts();
    buildScene();
}

void World::update(sf::Time dt)
{
    spawnEnemies();
    handleCollisions();

    if(mPlayerSpaceship->isDying())
        alivePlayer = false;

    if(alivePlayer)
    {
        while(!mCommandQueue.isEmpty())
            mSceneGraph.onCommand(mCommandQueue.pop(), dt);

        scrollView();
    }

    cleanOutterWorld();

    mSceneGraph.update(dt, mCommandQueue);
    mSceneGraph.cleanSceneGraph();


    /** Sounds **/
    mSounds.setListnerPosition(mPlayerSpaceship->getWorldPosition());
    mSounds.removeStoppedSounnds();
}

void World::scrollView()
{
    sf::Vector2f playerPosition = mPlayerSpaceship->getPosition();
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());

    float winSize = mWorldView.getSize().x;

    if(!mViewLocked)
    {
        if(((playerPosition.x > mWorldView.getCenter().x-winSize /4) ||
            (playerPosition.x < mWorldView.getCenter().x-winSize /4)) &&
            (playerPosition.x > winSize /4))
        {
            mWorldView.setCenter(playerPosition.x+winSize/4, mWorldView.getCenter().y);
            mBackground2View.setCenter(winSize/2 + (playerPosition.x-winSize/4)/2, mBackground2View.getCenter().y);
            mBackgroundView.setCenter(winSize/2 + (playerPosition.x-winSize/4)/4, mBackgroundView.getCenter().y);
        }
    }
}

bool matchesCategories(SceneNode::pair& colliders, Category::Type type1, Category::Type type2)
{
    unsigned int category1 = colliders.first->getSceneCategory();
    unsigned int category2 = colliders.second->getSceneCategory();

    // Make sure first pair entry has category type1 and second has type2
    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    else
    {
        return false;
    }
}

void World::handleCollisions()
{
    // Keep player's position inside the screen bounds, at least borderDistance units from the border
    sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
    const float borderDistance = 40.f;
    sf::Vector2f position = mPlayerSpaceship->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);
    position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
    position.y = std::max(position.y, viewBounds.top + borderDistance);
    position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
    mPlayerSpaceship->setPosition(position);

    //Triggers and handle View locks
    if(!mLevelLocks.empty())
    {
        if(mPlayerSpaceship->getPosition().x >= mLevelLocks.back()->x && !mLevelLocks.back()->triggered)
        {
            mViewLocked = true;
            mLevelLocks.back()->triggered = true;
        }

        if(mLevelLocks.back()->triggered)
        {
            if(mLevelLocks.back()->on)
            {
                mLevelLocks.back()->on = false;
                mCommandQueue.push(mLevelLocks.back()->releaseCondition);
            }
            else
            {
                mViewLocked = false;
                mLevelLocks.pop_back();
            }
        }
    }

    //Check pairs collisions
    std::set<SceneNode::pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

    for(SceneNode::pair pair : collisionPairs)
    {
        if (matchesCategories(pair, Category::PlayerSpaceship, Category::EnemySpaceship))
        {
            auto& player = static_cast<Spaceship&>(*pair.first);
            auto& enemy = static_cast<Spaceship&>(*pair.second);

            // Collision: Player damage = enemy's remaining HP
            player.takeDamage(enemy.getStats().life);
            enemy.kill();
        }

        else if (matchesCategories(pair, Category::AlliedSpaceship, Category::EnemyProjectile)
              || matchesCategories(pair, Category::EnemySpaceship, Category::AlliedProjectile))
        {
            auto& spaceship = static_cast<Spaceship&>(*pair.first);
            auto& projectile = static_cast<Projectile&>(*pair.second);

            if(!spaceship.isDying() && !projectile.isDying())
            {
                // Apply projectile damage to aircraft, kill projectile
                spaceship.takeDamage(projectile);
                projectile.kill();
            }
        }

        else if (matchesCategories(pair, Category::AlliedSpaceship, Category::Debris)
              || matchesCategories(pair, Category::EnemySpaceship, Category::Debris))
        {
            auto& spaceship = static_cast<Spaceship&>(*pair.first);
            auto& debris = static_cast<Debris&>(*pair.second);

            spaceship.takeDamage(debris.getHealthPoints());
            debris.kill();
        }

        else if (matchesCategories(pair, Category::Debris, Category::Projectile))
        {
            auto& debris = static_cast<Debris&>(*pair.first);
            auto& projectile = static_cast<Projectile&>(*pair.second);

            // Apply projectile damage to aircraft, kill projectile
            if(!projectile.isDying())
            {
                debris.takeDamage(projectile.getDamage());
                projectile.kill();
            }
        }

    }
}

void World::printSceneGraph()
{
    if(mSceneGraph.isSceneGraphChanged())
    {
        system("cls");
        mSceneGraph.printSceneGraph();
    }
}


void World::cleanOutterWorld()
{
    Command remove;
    remove.category = Category::Projectile | Category::Debris;
    remove.action = derivedAction<Entity>([this] (Entity& node, sf::Time)
    {
        if(!this->getViewBounds(mWorldBounds.width, 200).intersects(node.getBoundingRect()))
            node.destroy();
    });

    Command removeEnnemiesProjectile;
    removeEnnemiesProjectile.category = Category::EnemyProjectile;
    removeEnnemiesProjectile.action = derivedAction<Entity>([this] (Entity& node, sf::Time)
    {
        if(!this->getViewBounds(300, 200).intersects(node.getBoundingRect()))
            node.destroy();
    });

    mCommandQueue.push(remove);
    mCommandQueue.push(removeEnnemiesProjectile);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

void World::draw()
{
    mWindow.setView(mBackgroundView);
    mWindow.draw(*mSceneLayers[Background]);

    mWindow.setView(mBackground2View);
    mWindow.draw(*mSceneLayers[Background2]);

    mWindow.setView(mWorldView);
    mWindow.draw(*mSceneLayers[ProjectileLayer]);
    mWindow.draw(*mSceneLayers[Space]);

    mWindow.setView(mWindow.getDefaultView());
    sf::Text debug;
    debug.setFont(mFonts.get(Fonts::Main));
    debug.setFillColor(sf::Color::White);
    debug.setCharacterSize(20);

    debug.setPosition(10, 10);
    debug.setString("Player : " + toString(mPlayerSpaceship->getPosition().x) + ", " + toString(mPlayerSpaceship->getPosition().y));
    mWindow.draw(debug);

    debug.setPosition(10, 30);
    debug.setString("BackView : " + toString(mBackgroundView.getCenter().x));
    mWindow.draw(debug);

    debug.setPosition(10, 50);
    debug.setString("BackView2 : " + toString(mBackground2View.getCenter().x));
    mWindow.draw(debug);

    debug.setPosition(10, 70);
    debug.setString("WorldView : " + toString(mWorldView.getCenter().x));
    mWindow.draw(debug);

    mSceneGraph.SceneCount = 0;
    mSceneGraph.isSceneGraphChanged();
    debug.setPosition(10, 90);
    debug.setString("Object Count : " + toString(mSceneGraph.SceneCount));
    mWindow.draw(debug);

}

void World::loadTextures()
{
    mTextures.load(Textures::Khaal, "Ressources/Sprite/Player/Player.png");
    mTextures.load(Textures::Intercepter, "Ressources/Sprite/Ennemies/Intercepteur.png");
    mTextures.load(Textures::Blade, "Ressources/Sprite/Ennemies/Blade.png");
    mTextures.load(Textures::SpaceLvl1, "Ressources/Sprite/background3.jpg");
    mTextures.load(Textures::Bullet, "Ressources/Sprite/LaserBleu.png");
    mTextures.load(Textures::Missile, "Ressources/Sprite/missile.png");
    mTextures.load(Textures::Particle, "Ressources/Sprite/Particle.png");
    mTextures.load(Textures::LaserBlue, "Ressources/Sprite/LaserBleu.png");
    mTextures.load(Textures::LaserRed, "Ressources/Sprite/LaserRouge.png");
    mTextures.load(Textures::LaserGun, "Ressources/Sprite/Player/canon.png");
    mTextures.load(Textures::Khaal_Explode, "Ressources/Sprite/Player/khaal_explode.png");
    mTextures.load(Textures::Classic_Explode, "Ressources/Sprite/Ennemies/classic_explode.png");
    mTextures.load(Textures::LaserBlue_Fire, "Ressources/Sprite/blast-CP.png");
    mTextures.load(Textures::Planet1, "Ressources/Levels/planet1.png");

    mTextures.load(Textures::AsteroidDebris, "Ressources/Sprite/Asteroids/asteroid1.png");
    mTextures.load(Textures::SpaceshipDebris, "Ressources/Sprite/SpaceshipDebris/spaceship1.png");

    mIcons.load(Icons::Laser1, "Ressources/System/Icon/CP_1.png");
    mIcons.load(Icons::Laser2, "Ressources/System/Icon/DCP_1.png");
    mIcons.load(Icons::Laser3, "Ressources/System/Icon/DCP_1.png");
    mIcons.load(Icons::Pouclier, "Ressources/System/Icon/SH_1.png");

}

void World::loadFonts()
{
    mFonts.load(Fonts::Main, "Ressources/consola.ttf");
    mFonts.load(Fonts::KLM, "Ressources/TYPO KLM.ttf");
}

bool World::hasAlivePlayer()
{
    return alivePlayer;
}

void World::buildScene()
{
    // Initialize Sound node
    std::unique_ptr<SoundNode> sounds(new SoundNode(mSounds));
    mSceneGraph.attachChild(std::move(sounds));

    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type cat;
        switch(i)
        {
            case Layer::Background:
            case Layer::Background2:
                cat = Category::SceneBackgroundLayer;
                break;
            case Layer::Space:
                cat = Category::SceneAirLayer;
                break;
            case Layer::ProjectileLayer:
                cat = Category::SceneProjectileLayer;
                break;

            default:
                cat = Category::None;
                break;
        }

        SceneNode::ptr layer(new SceneNode(cat));
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = mTextures.get(Textures::SpaceLvl1);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture));
    background->setPosition(0.f, 0.f);
    mSceneLayers[Background]->attachChild(std::move(background));

    // Add animation to the scene
    std::unique_ptr<AnimationNode> turningPlanet(new AnimationNode(Animation::Planet1, mTextures));
    turningPlanet->setPosition(500.f, 500.f);
    mSceneLayers[Layer::Background2]->attachChild(std::move(turningPlanet));

    //Add particles to the world
    std::unique_ptr<ParticleNode> blueSmokeNode(new ParticleNode(Particle::BlueSmoke, mTextures));
    std::unique_ptr<ParticleNode> redSmokeNode(new ParticleNode(Particle::RedSmoke, mTextures));
    mSceneLayers[Layer::ProjectileLayer]->attachChild(std::move(blueSmokeNode));
    mSceneLayers[Layer::ProjectileLayer]->attachChild(std::move(redSmokeNode));

    // Add player's aircraft
    std::unique_ptr<Spaceship> leader(new Spaceship(Spaceship::Khaal, mTextures, mFonts, mIcons));
    mPlayerSpaceship = leader.get();
    mPlayerSpaceship->setPosition(mSpawnPosition);
    mSceneLayers[Space]->attachChild(std::move(leader));
    alivePlayer = true;

    //Add Asteroid generator
    std::unique_ptr<AsteroidGenerator> asteroidGenerator(new AsteroidGenerator(mTextures));
    asteroidGenerator->speed.setRange(5.f, 100.f);
    asteroidGenerator->angle.setRange(45, 135.f);
    asteroidGenerator->spin.setRange(-60.f, 60.f);
    asteroidGenerator->frequency.setRange(2.f, 5.f);
    asteroidGenerator->scale.setRange(0.1f, 1.f);
    asteroidGenerator->setPosition(2500, -100);
    asteroidGenerator->start();
    mSceneLayers[Space]->attachChild(std::move(asteroidGenerator));


    // Add ennemies and view lock
    addEnemy(Spaceship::Intercepter, 1500.f, 0.f);
    addLevelLock(1000);

    addEnemy(Spaceship::Intercepter,    2500.f, 200.f);
    addEnemy(Spaceship::Blade,    2400.f, 0);
    addEnemy(Spaceship::Intercepter, 2500.f, -200.f);
    addLevelLock(2000);

    addEnemy(Spaceship::Blade, 3400.f, -140.f);
    addEnemy(Spaceship::Blade, 3600.f, 70.f);
    addEnemy(Spaceship::Blade, 3400.f, 140.f);
    addEnemy(Spaceship::Blade, 3600.f, -70.f);
    addLevelLock(3000);
}


void World::addLevelLock(float x)
{
    LevelLock::ptr Lock(new LevelLock(x));

    mLevelLocks.push_back(std::move(Lock));

    auto SortByX = [] (const LevelLock::ptr &LockA, const LevelLock::ptr &LockB)
    {
        return LockA->x > LockB->x;
    };

    std::sort(mLevelLocks.begin(), mLevelLocks.end(), SortByX);
}

void World::addEnemy(Spaceship::Type type, float x, float y)
{
    mEnemySpawnPoints.push_back(SpawnPoint(type, mSpawnPosition.x + x, mSpawnPosition.y - y));

    auto SortByX = [] (SpawnPoint a, SpawnPoint b)
    {
        return a.x > b.x;
    };

    std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), SortByX);
}

void World::spawnEnemies()
{
    while (!mEnemySpawnPoints.empty() && mEnemySpawnPoints.back().x < getViewBounds(0).left+mWorldView.getSize().x)
    {
        SpawnPoint spawn = mEnemySpawnPoints.back();

        std::unique_ptr<Spaceship> enemy(new Spaceship(spawn.type, mTextures, mFonts, mIcons));
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setRotation(0);

        mSceneLayers[Space]->attachChild(std::move(enemy));

        // Enemy is spawned, remove from the list to spawn
        mEnemySpawnPoints.pop_back();
    }
}

sf::FloatRect World::getViewBounds(float offset)
{
    return sf::FloatRect(mWorldView.getCenter() - sf::Vector2f(offset, offset) - mWorldView.getSize() / 2.f, mWorldView.getSize()+sf::Vector2f(offset, offset));
}

sf::FloatRect World::getViewBounds(float xOffset, float yOffset)
{
    return sf::FloatRect(mWorldView.getCenter() - sf::Vector2f(xOffset, yOffset) - mWorldView.getSize() / 2.f, mWorldView.getSize()+sf::Vector2f(xOffset, yOffset));
}

World::SpawnPoint::SpawnPoint(Spaceship::Type type, float x, float y) : type(type), x(x), y(y)
{
}
