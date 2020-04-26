#include "ScaleKey.h"

ScaleKey::ScaleKey(unsigned int pMode, float pDuration) : AnimationKey(pMode, pDuration)
{
    ScaleValue = sf::Vector2f(0, 0);
    AchievedScale = ScaleValue;
}

void ScaleKey::setScale(sf::Vector2f Scale)
{
    ScaleValue = Scale;
}

void ScaleKey::setScale(float pScale)
{
    ScaleValue = sf::Vector2f(pScale, pScale);
}

sf::Vector2f ScaleKey::getScaleKey()
{
    return AchievedScale;
}

void ScaleKey::Update()
{
    AchievedScale = Completion*ScaleValue;
}
