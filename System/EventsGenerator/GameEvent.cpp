#include "GameEvent.h"

GameEvent::GameEvent()
{

}

void GameEvent::setPeriod(float Min, float Max)
{
    if((Min >= 0.0) && (Max >= 0.0))
    {
        MinPerdiod = Min;
        MaxPeriod = Max;
        AveragePeriod = (Min+Max)/2;
    }
}

void GameEvent::setPeriod(float Min, float Average, float Max)
{
    if((Min >= 0.0) && (Max >= 0.0) && (Average >= Min) && (Average <= Max))
    {
        MinPerdiod = Min;
        MaxPeriod = Max;
        AveragePeriod = Average;
    }
}


void GameEvent::setNumber(unsigned int Min, unsigned int Max)
{
    if((Min >= 0.0) && (Max >= 0.0))
    {
        MinEventNumber = Min;
        MaxEventNumber = Max;
        AverageEventNumber = (Min+Max)/2;
    }
}

void GameEvent::setNumber(unsigned int Min, unsigned int Average, unsigned int Max)
{
    if((Min >= 0.0) && (Max >= 0.0) && (Average >= Min) && (Average <= Max))
    {
        MinEventNumber = Min;
        MaxEventNumber = Max;
        AverageEventNumber = Average;
    }
}


void GameEvent::HandleTime(float ElapsedTime)
{

}

