#ifndef SCALEKEY_H
#define SCALEKEY_H

#include "../AnimationKey.h"

class ScaleKey : public AnimationKey
{
    public:
        ScaleKey(unsigned int pMode, float pDuration);

        void setScale(sf::Vector2f Scale);
        void setScale(float pScale);
        sf::Vector2f getScaleKey();
        sf::Vector2f getCurrentScale();
        virtual void Update();

    protected:
        sf::Vector2f ScaleValue;
        sf::Vector2f AchievedScale;
};

#endif // SCALEKEY_H
