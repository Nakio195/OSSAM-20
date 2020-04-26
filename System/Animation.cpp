#include "Animation.h"
#include "System/Utilities.h"
#include "Entities/DataTables.h"

namespace
{
    const std::vector<AnimationData > Table = initAnimationData();
}

Animation::Animation(Animation::Type type, const TextureHolder& textures)
{
    mAnimationTimer.setMode(Table[type].timerMode);
    mAnimationTimer.setPeriod(Table[type].period);
    mMode = Table[type].mode;

    mSprite.setTexture(textures.get(Table[type].texture));

    setFrame(Table[type].frameCount, Table[type].rect);

    //Frame Mode
    mCurrentFrame = 0;

    // Key Mode
    mTranslationKeys = Table[type].translationKeys;
    mRotationKeys = Table[type].rotationKeys;
    mScaleKeys = Table[type].scaleKeys;

    mCurrentRotationKey = 0;
    mCurrentScaleKey = 0;
    mCurrentTranslationKey = 0;
    mRotationSequence = Finished;
    mTranslationSequence = Finished;
    mScaleSequence = Finished;

    pushStartCommand = false;
    pushRepeatCommand = false;
    pushEndCommand = false;
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(isRunning())
    {
        states.transform *= getTransform();
        target.draw(mSprite, states);
    }
}

void Animation::setTexture(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
    centerOrigin(mSprite);
}


void Animation::setFrame(unsigned int pFrame, sf::IntRect FrameSize)
{
    mFrame = pFrame;
    mFrameRect = FrameSize;
    mSprite.setOrigin(FrameSize.width/2, FrameSize.height/2);
}


sf::IntRect Animation::getFrameRect()
{
    return mFrameRect;
}


void Animation::addKey(RotationKey Key)
{
    mRotationKeys.push_back(Key);
}


void Animation::addKey(TranslationKey Key)
{
    mTranslationKeys.push_back(Key);
}


void Animation::addKey(ScaleKey Key)
{
    mScaleKeys.push_back(Key);
}


bool Animation::isRunning() const
{
    return mAnimationTimer.isRunning();
}


void Animation::setTimerMode(Timer::Mode pMode)
{
    mAnimationTimer.setMode(pMode);
}


unsigned int Animation::getTimerMode() const
{
    return mAnimationTimer.getMode();
}


void Animation::setPeriod(float pPeriod)
{
    mAnimationTimer.setPeriod(pPeriod);
}


float Animation::getPeriod() const
{
    return mAnimationTimer.getPeriod();
}


void Animation::start(float Period)
{
    mAnimationTimer.StartTimer(Period);

    if(mStartCommand.category != Category::Uninitialized)
        pushStartCommand = true;

    if(mMode == Animation::Sprite)
    {
        setTimerMode(Timer::Continuous);

        if(mCurrentFrame < mFrame)
        {
            sf::IntRect Rect;
            Rect.height = mFrameRect.height;
            Rect.width = mFrameRect.width;
            Rect.top = 0;
            Rect.left = static_cast<int>(mCurrentFrame)*mFrameRect.width;

            mSprite.setTextureRect(Rect);
            mCurrentFrame++;
        }

        else
            stop();
    }

    if(mMode == Animation::KeySequence)
    {
        mCurrentRotationKey = 0;
        mCurrentScaleKey = 0;
        mCurrentTranslationKey = 0;

        if(mRotationKeys.size() == 0 && mTranslationKeys.size() == 0 && mScaleKeys.size() == 0)
            stop();

        else if(mRotationKeys.size() > 0)
            mRotationSequence = Running;

        else if(mTranslationKeys.size() > 0)
            mTranslationSequence = Running;

        else if(mScaleKeys.size() > 0)
            mScaleSequence = Running;
    }
}


void Animation::stop()
{
    mAnimationTimer.StopTimer();

    if(mMode == Animation::Sprite)
        mCurrentFrame = 0;

    if(mMode == Animation::KeySequence)
    {
        mCurrentRotationKey = 0;
        mCurrentScaleKey = 0;
        mCurrentTranslationKey = 0;
    }

    if(mEndCommand.category != Category::Uninitialized)
        pushEndCommand = true;
}


void Animation::pause()
{
    mAnimationTimer.PauseTimer();
}


void Animation::release()
{
    mAnimationTimer.ReleaseTimer();
}


void Animation::play(sf::Time ElapsedTime, CommandQueue &Commands)
{
    if(mMode != Animation::KeySequence)
    {
        mAnimationTimer.Count(ElapsedTime);

        if(mAnimationTimer.Triggered())
        {
            if(mAnimationTimer.getMode() == Timer::Continuous)
                start();

            else
                stop();
        }
    }

    if(mMode == Animation::KeySequence)
    {
        //Rotation Keys
        if(mCurrentRotationKey < mRotationKeys.size() && mRotationSequence == Animation::Running)
        {
            RotationKey *Temp = &mRotationKeys.at(mCurrentRotationKey);

            if(Temp->getStatus() == AnimationKey::Stopped)
                Temp->start();

            if(Temp->getStatus() == AnimationKey::Running)
            {
                Temp->play(ElapsedTime);
                mSprite.setRotation(Temp->getCurrentRotation());
            }

            if(Temp->getStatus() == AnimationKey::Finished)
            {
                Temp->stop();
                mCurrentRotationKey++;

                if(mCurrentRotationKey >= mRotationKeys.size())
                    mRotationSequence = Animation::Finished;
            }
        }

        //Translation Keys
        if(mCurrentRotationKey < mRotationKeys.size())
        {

        }

        //Scale Keys
        if(mCurrentRotationKey < mRotationKeys.size())
        {

        }

        if((mRotationSequence == Finished) && (mTranslationSequence == Finished) && (mScaleSequence == Finished))
        {
            if(mAnimationTimer.getMode() == Timer::Continuous)
                start();
            else
                stop();
        }
    }

    //Pushing requested commands
    if(pushStartCommand)
    {
        Commands.push(mStartCommand);
        pushStartCommand = false;
    }

    if(pushRepeatCommand)
    {
        Commands.push(mRepeatCommand);
        pushRepeatCommand = false;
    }

    if(pushEndCommand)
    {
        Commands.push(mEndCommand);
        pushEndCommand = false;
    }

}


void Animation::setStartAction(Command Action)
{
    mStartCommand = Action;
}


void Animation::setRepeatAction(Command Action)
{
    mRepeatCommand = Action;
}


void Animation::setEndAction(Command Action)
{
    mEndCommand = Action;
}
