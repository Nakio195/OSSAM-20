#ifndef ANIMATION_H
#define ANIMATION_H

#include "Timer.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>

#include "System/AnimationKey/RotationKey.h"
#include "System/AnimationKey/TranslationKey.h"
#include "System/AnimationKey/ScaleKey.h"
#include "Ressources/RessourceIdentifiers.h"
#include "System/Commands/Command.h"

using namespace std;

class Animation : public sf::Drawable, public sf::Transformable
{
    public:
        enum Type{None,
                  Khaal_Explode,
                  Classic_Explode,
                  LaserBlue_Fire,
                  Planet1,
                  AnimationsCount
                 };

    public:
        enum Mode{Event, Sprite, KeySequence};
        enum Sequence{Running, Finished};

    public:
        Animation(Animation::Type type, const TextureHolder& textures);
        Animation(const sf::Texture& texture, sf::Time period, Animation::Mode animationMode, Timer::Mode timerMode = Timer::OneShot);

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
        void setTexture(const sf::Texture& texture);
        sf::Texture* getTexture();

        // Frame Mode
        void setFrame(unsigned int pFrame, sf::IntRect FrameSize);
        sf::IntRect getFrameRect();

        // Key Mode
        void addKey(RotationKey Key);
        void addKey(TranslationKey Key);
        void addKey(ScaleKey Key);

        void setTimerMode(Timer::Mode pMode);
        unsigned int getTimerMode() const;
        void setPeriod(float pPeriod);
        float getPeriod() const;

        void start(float Period = 0);
        void stop();

        void pause();
        void release();

        void play(sf::Time ElapsedTime, CommandQueue &Commands);
        bool isRunning() const;

        void setStartAction(Command Action);
        void setRepeatAction(Command Action);
        void setEndAction(Command Action);

    private:
        // Core
        sf::Sprite mSprite;
        Timer mAnimationTimer;
        Animation::Mode mMode;

        //Frame Mode
        sf::IntRect mFrameRect;
        unsigned int mFrame;
        unsigned int mCurrentFrame;

        // Key Mode
        std::vector<RotationKey> mRotationKeys;
        std::vector<TranslationKey> mTranslationKeys;
        std::vector<ScaleKey> mScaleKeys;

        unsigned int mCurrentRotationKey;
        unsigned int mCurrentTranslationKey;
        unsigned int mCurrentScaleKey;

        bool mRotationSequence;
        bool mTranslationSequence;
        bool mScaleSequence;

        //Callback
        bool pushStartCommand;
        bool pushRepeatCommand;
        bool pushEndCommand;

        Command mStartCommand;
        Command mRepeatCommand;
        Command mEndCommand;
};

#endif // ANIMATION_H
