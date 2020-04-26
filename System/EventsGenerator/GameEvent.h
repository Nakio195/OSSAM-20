#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include "../Timer.h"

class GameEvent
{
    public:
        GameEvent();
        virtual void Generate() = 0;

        void setPeriod(float Min, float Max);
        void setPeriod(float Min, float Average, float Max);

        void setNumber(unsigned int Min, unsigned int Max);
        void setNumber(unsigned int Min, unsigned int Average, unsigned int Max);

        void HandleTime(float ElapsedTime);

    protected:
        float MinPerdiod;
        float AveragePeriod;
        float MaxPeriod;

        unsigned int MinEventNumber;
        unsigned int AverageEventNumber;
        unsigned int MaxEventNumber;

        Timer GenerationTimer;
};

#endif // GAMEEVENT_H
