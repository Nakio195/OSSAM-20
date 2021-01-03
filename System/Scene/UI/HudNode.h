#ifndef ATH_H
#define ATH_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Entities/Spaceship.h"

using namespace std;

class HudNode : public SceneNode
{
    public:
    enum Type{
        Player,
        HudCount
    };

    public:
        HudNode(Spaceship *pParent, const TextureHolder& textures);
        void setBackground(string Path);
        void setHealthBar(sf::Color Color, sf::Vector2f Size, sf::Vector2f Relative = sf::Vector2f(0,0));
        void setShieldBar(sf::Color Color, sf::Vector2f Size, sf::Vector2f Relative = sf::Vector2f(0,0));

        void Fix(sf::Vector2f FixPosition);
        void Unfix();
        bool isFixed();

        virtual unsigned int getSceneCategory() const;

        void updateCurrent(sf::Time dt, CommandQueue &) override;

    private:
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        Spaceship *mParent;
        sf::Sprite mSprite;

        bool mFixed;
        sf::Vector2f mFixedPosition;

        sf::RectangleShape mHealthBar;
        sf::Color mHealth_Color;
        sf::Vector2f mHealth_Dimensions;
        sf::Vector2f mHealth_RelativePos;

        sf::RectangleShape mShieldBar;
        sf::Color mShield_Color;
        sf::Vector2f mShield_Dimensions;
        sf::Vector2f mShield_RelativePos;
};

#endif // ATH_H
