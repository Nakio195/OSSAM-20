#include "ATH.h"

/**
 * @brief ATH::ATH
 * @param pParent
 * @param PathToBackground
 */

ATH::ATH(Spaceship *pParent, string PathToBackground) : Sprite()
{
    Parent = pParent;
    Fixed = false;

    Background_Texture = new sf::Texture();

    if(PathToBackground != string(""))
    {
        Background_Texture->loadFromFile(PathToBackground);
        this->setTexture(*Background_Texture);
    }

    HealthBar.setOutlineColor(sf::Color(0, 0, 0));
    ShieldBar.setOutlineColor(sf::Color(0, 0, 0));
    HealthBar.setOutlineThickness(1.0);
    ShieldBar.setOutlineThickness(1.0);
}


void ATH::Fix(sf::Vector2f FixPosition)
{
    Fixed = true;
    FixedPosition = FixPosition;
}

void ATH::Unfix()
{
    Fixed = false;
}

bool ATH::isFixed()
{
    return Fixed;
}

void ATH::setBackground(string Path)
{
    Background_Texture->loadFromFile(Path);
    this->setTexture(*Background_Texture);
}

void ATH::setHealthBar(sf::Color Color, sf::Vector2f Size, sf::Vector2f Relative)
{
    HealthBar.setFillColor(Color);
    Health_Color = Color;
    Health_Dimensions = Size;
    Health_RelativePos = Relative;
}

void ATH::setShieldBar(sf::Color Color, sf::Vector2f Size, sf::Vector2f Relative)
{
    ShieldBar.setFillColor(Color);
    Shield_Color = Color;
    Shield_Dimensions = Size;
    Shield_RelativePos = Relative;
}

void ATH::draw(sf::RenderWindow *Window)
{
    float Current, Max;
    float Ratio;

    if(Fixed)
        this->setPosition(FixedPosition);

    else
        this->setPosition(Parent->getPosition());

    HealthBar.setPosition(sf::Vector2f(this->getPosition().x + Health_RelativePos.x, this->getPosition().y + Health_RelativePos.y));
    Current = Parent->getStats().life;
    Max = Parent->getMaxStats().life;
    Ratio = Current/Max;
    HealthBar.setFillColor(sf::Color((Health_Color.r/Ratio < 180) ? (Health_Color.r/Ratio) : 180, Health_Color.g*Ratio, Health_Color.b*Ratio));
    HealthBar.setSize(sf::Vector2f(Ratio*Health_Dimensions.x, Health_Dimensions.y));

    ShieldBar.setPosition(sf::Vector2f(this->getPosition().x + Shield_RelativePos.x, this->getPosition().y + Shield_RelativePos.y));
    Current = Parent->getStats().shield;
    Max = Parent->getMaxStats().shield;
    Ratio = Current/Max;
    ShieldBar.setFillColor(sf::Color(Shield_Color.r*Ratio, Shield_Color.g*Ratio, (Shield_Color.b/Ratio < 180) ? (Shield_Color.b/Ratio) : 180));
    ShieldBar.setSize(sf::Vector2f(Ratio*Shield_Dimensions.x, Shield_Dimensions.y));

    Window->draw(*this);
    Window->draw(HealthBar);
    Window->draw(ShieldBar);
}
