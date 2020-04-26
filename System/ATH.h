#ifndef ATH_H
#define ATH_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Entities/Spaceship.h"

using namespace std;

class ATH : public sf::Sprite
{
    public:
        ATH(Spaceship *pParent, string PathToBackground = "");
        void setBackground(string Path);
        void setHealthBar(sf::Color Color, sf::Vector2f Size, sf::Vector2f Relative = sf::Vector2f(0,0));
        void setShieldBar(sf::Color Color, sf::Vector2f Size, sf::Vector2f Relative = sf::Vector2f(0,0));

        void Fix(sf::Vector2f FixPosition);
        void Unfix();
        bool isFixed();

        void draw(sf::RenderWindow *Window);

    private:
        Spaceship *Parent;
        bool Fixed;
        sf::Vector2f FixedPosition;


        sf::Texture *Background_Texture;

        sf::RectangleShape HealthBar;
        sf::Color Health_Color;
        sf::Vector2f Health_Dimensions;
        sf::Vector2f Health_RelativePos;

        sf::RectangleShape ShieldBar;
        sf::Color Shield_Color;
        sf::Vector2f Shield_Dimensions;
        sf::Vector2f Shield_RelativePos;
};

#endif // ATH_H
