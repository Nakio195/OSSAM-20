#include "RotationKey.h"

RotationKey::RotationKey(float Value, bool Direction, float pDuration) : AnimationKey(AnimationKey::Rotation, pDuration)
{
    RotationValue = Value;
    AchievedRotation = 0.0;
    RotationDirection = Direction;
}

void RotationKey::setRotation(float Rotation, bool Direction)
{
    RotationValue = Rotation;
    RotationDirection = Direction;
}

float RotationKey::getRotationKey()
{
    return RotationValue;
}

float RotationKey::getCurrentRotation()
{
    return AchievedRotation;
}

bool RotationKey::getRotationDirection()
{
    return RotationDirection;
}


void RotationKey::update()
{
    AchievedRotation = Completion*RotationValue;
}

float RotationKey::getStepRotation()
{

}
