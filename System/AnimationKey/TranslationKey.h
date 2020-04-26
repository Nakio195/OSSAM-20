#ifndef TRANSLATIONKEY_H
#define TRANSLATIONKEY_H

#include "../AnimationKey.h"

class TranslationKey : public AnimationKey
{
    public:
        TranslationKey(unsigned int pMode, float Duration);

        void setTranslation(sf::Vector2f Translation);
        sf::Vector2f getTranslationKey();
        sf::Vector2f getCurrentTranslation();
        virtual void Update();

    private:
        sf::Vector2f TranslationValue;
        sf::Vector2f AchievedTranslation;
};

#endif // TRANSLATIONKEY_H
