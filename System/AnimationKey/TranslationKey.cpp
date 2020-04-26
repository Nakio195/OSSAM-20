#include "TranslationKey.h"

TranslationKey::TranslationKey(unsigned int pMode, float pDuration) : AnimationKey(pMode, pDuration)
{
    TranslationValue = sf::Vector2f(0, 0);
    AchievedTranslation = TranslationValue;
}


void TranslationKey::setTranslation(sf::Vector2f Translation)
{
    TranslationValue = Translation;
}

sf::Vector2f TranslationKey::getTranslationKey()
{
    return TranslationValue;
}

sf::Vector2f TranslationKey::getCurrentTranslation()
{
    return AchievedTranslation;
}

void TranslationKey::Update()
{

}
