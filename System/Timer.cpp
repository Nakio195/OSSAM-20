#include "Timer.h"

#include <SFML/System/Time.hpp>

/**
 * @brief Timer::Timer
 * @param pPeriod
 * @param pMode
 */

Timer::Timer(float pPeriod, unsigned int pMode)
{
    mPeriod = pPeriod;
    mMode = pMode;

    mCounter = 0;

    mRunning = false;
    mTrigger = false;
}


Timer::Timer(sf::Time pPeriod, unsigned int pMode)
{
    mPeriod = pPeriod.asSeconds();
    mMode = pMode;

    mCounter = 0;

    mRunning = false;
    mTrigger = false;
}


bool Timer::isRunning() const
{
    if(mCounter <= mPeriod && mRunning == false)
        return false;
    else
        return true;
}

float Timer::getPeriod() const
{
    return mPeriod;
}

void Timer::setPeriod(float pPeriod)
{
    mPeriod = pPeriod;
    mCounter = 0;
}

void Timer::setPeriod(sf::Time pPeriod)
{
    mPeriod = pPeriod.asSeconds();
    mCounter = 0.f;
}

float Timer::getCounter() const
{
    return mCounter;
}

void Timer::Count(float pElapsedTime)
{
    if(mRunning)
    {
        mCounter += pElapsedTime;

        if(mCounter >= mPeriod)
            mTrigger = 1;
    }
}

void Timer::Count(sf::Time pElapsedTime)
{
    if(mRunning)
    {
        mCounter += pElapsedTime.asSeconds();

        if(mCounter >= mPeriod)
            mTrigger = 1;
    }
}

bool Timer::Triggered() // Read timer Trigger and reset it if enabled
{
    bool TriggerValue;

    TriggerValue = mTrigger;

    if(mTrigger == true)
    {
        mTrigger = false;

        if(mMode == OneShot)
        {
            mRunning = false;
            mCounter = 0;
        }

        else if(mMode == Continuous)
        {
            mRunning = true;
            mCounter = 0;
        }
    }

    return TriggerValue;
}

void Timer::StartTimer(float pPeriod) // Start Timer from beginning (see ReleaseTimer() and PauseTimer() )
{
    if(pPeriod != 0.f)
        mPeriod = pPeriod;

    mCounter = 0;
    mRunning = true;
}

void Timer::StopTimer() // Stop timer and reset it
{
    mRunning = 0;
    mCounter = 0;
}


void Timer::PauseTimer()
{
    mRunning = false;
}

void Timer::ReleaseTimer()
{
    mRunning = true;
}

unsigned int Timer::getMode() const
{
    return mMode;
}

void Timer::setMode(unsigned int pMode)
{
    if(pMode == Continuous || pMode == OneShot)
        mMode = pMode;
}


float Timer::getProgression() const
{
    return mCounter/mPeriod;
}
