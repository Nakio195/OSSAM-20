#ifndef TITLESTATE_H
#define TITLESTATE_H

#include <SFML/Graphics.hpp>

#include "Ressources/RessourceHolder.h"
#include "System/States/StateStack.h"

class TitleState : public State
{
    public:
        TitleState(StateStack& stack, Context context);
        virtual void draw();
        virtual bool update(sf::Time dt);
        virtual bool handleEvent(const sf::Event &event);

    private:
        sf::Sprite mBackgroundSprite;
        sf::Sprite mBackgroundSprite2;
        sf::View mTitleView;

        unsigned int mTitleCount;
        unsigned int mCurrentTitle;
        float mBlend;
        bool mBlendOver;
        bool mBlendDirection;
        sf::RectangleShape mBlendShape;
};

#endif // TITLESTATE_H
