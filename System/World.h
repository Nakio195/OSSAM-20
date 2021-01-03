#ifndef WORLD_H
#define WORLD_H

#include "System/Scene/SceneNode.h"
#include "System/Scene/SpriteNode.h"
#include "Ressources/RessourceIdentifiers.h"
#include "Ressources/RessourceHolder.h"
#include "Entities/Spaceship.h"
#include "Entities/Debris.h"
#include "System/Commands/Command.h"
#include "System/SoundPlayer.h"
#include <math.h>

class World : private sf::NonCopyable
{
    public:
        World(sf::RenderWindow& window, SoundPlayer& sounds);
        void update(sf::Time dt);
        void draw();

        CommandQueue& getCommandQueue();

        bool hasAlivePlayer();
        void printSceneGraph();

    private:
        void loadTextures();
        void loadFonts();
        void buildScene();

        void addEnemy(Spaceship::Type type, float x, float y);
        void addLevelLock(float x);
        void spawnEnemies();
        void cleanOutterWorld();

        void scrollView();

        void handleCollisions();
        sf::FloatRect getViewBounds(float offset = 0.f);
        sf::FloatRect getViewBounds(float xOffset, float yOffset);


    private:
        enum Layer{Background, Background2, ProjectileLayer, Space, LayerCount};

        struct SpawnPoint
        {
            SpawnPoint(Spaceship::Type type, float x, float y);

            Spaceship::Type type;
            float x;
            float y;
        };

        class LevelLock
        {
            public:
            typedef std::unique_ptr<LevelLock> ptr;

            LevelLock(float pX)
            {
                x = pX;
                on = true;
                triggered = false;
                releaseCondition.category = Category::EnemySpaceship;
                releaseCondition.action = [this] (SceneNode& node, sf::Time) {
                    this->on = !node.isDead();
                };
            }

            private:
            LevelLock(const LevelLock& cop);

            public:
            Command releaseCondition;
            bool on;
            bool triggered;
            float x;
        };

    private:
        sf::RenderWindow& mWindow;
        sf::View mWorldView;

        sf::View mBackgroundView;
        sf::View mBackground2View;

        SoundPlayer& mSounds;
        TextureHolder mTextures;
        IconHolder mIcons;
        FontHolder mFonts;

        CommandQueue mCommandQueue;

        SceneNode mSceneGraph;
        std::array<SceneNode*, LayerCount>	mSceneLayers;

        sf::FloatRect mWorldBounds;
        sf::Vector2f mSpawnPosition;
        float mScrollSpeed;

        bool alivePlayer;
        bool mViewLocked;

        Spaceship* mPlayerSpaceship;
        std::vector<SpawnPoint> mEnemySpawnPoints;
        std::vector<LevelLock::ptr> mLevelLocks;
};

#endif // WORLD_H
