#ifndef ROTATIONKEY_H
#define ROTATIONKEY_H

#include "../AnimationKey.h"

class RotationKey : public AnimationKey
{
    public:
        RotationKey(float Value, bool Direction, float pDuration);

        void setRotation(float Rotation, bool Direction);
        float getRotationKey();
        float getCurrentRotation();
        bool getRotationDirection();

        virtual void update();

        float getStepRotation();

    protected:
        float RotationValue;
        bool RotationDirection;

        float StepRotation;
        float AchievedRotation;
};

#endif // ROTATIONKEY_H
