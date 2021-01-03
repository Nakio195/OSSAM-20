#include "HudNode.h"

/**
 * @brief HudNode::HudNode
 * @param pParent
 * @param PHudNodeToBackground
 */

HudNode::HudNode(Spaceship *pParent, const TextureHolder& textures) : mSprite(textures)
{
    if(pParent != nullptr)
        mParent = pParent;
    mFixed = false;

    Background_Texture = new sf::Texture();

    mHealthBar.setOutlineColor(sf::Color(0, 0, 0));
    mShieldBar.setOutlineColor(sf::Color(0, 0, 0));
    mHealthBar.setOutlineThickness(1.0);
    mShieldBar.setOutlineThickness(1.0);
}


void HudNode::Fix(sf::Vector2f FixPosition)
{
    mFixed = true;
    mFixedPosition = FixPosition;
}

void HudNode::Unfix()
{
    mFixed = false;
}

bool HudNode::isFixed()
{
    return mFixed;
}

void HudNode::updateCurrent(sf::Time dt, CommandQueue &)
{
    float Current, Max;
    float Ratio;

    if(mFixed)
        setPosition(mFixedPosition);

    else
        this->setPosition(mParent->getPosition());

    mHealthBar.setPosition(sf::Vector2f(this->getPosition().x + mHealth_RelativePos.x, this->getPosition().y + mHealth_RelativePos.y));
    Current = mParent->getStats().life;
    Max = mParent->getMaxStats().life;
    Ratio = Current/Max;
    mHealthBar.setFillColor(sf::Color((mHealth_Color.r/Ratio < 180) ? (mHealth_Color.r/Ratio) : 180, mHealth_Color.g*Ratio, mHealth_Color.b*Ratio));
    mHealthBar.setSize(sf::Vector2f(Ratio*mHealth_Dimensions.x, mHealth_Dimensions.y));

    mShieldBar.setPosition(sf::Vector2f(this->getPosition().x + mShield_RelativePos.x, this->getPosition().y + mShield_RelativePos.y));
    Current = mParent->getStats().shield;
    Max = mParent->getMaxStats().shield;
    Ratio = Current/Max;
    mShieldBar.setFillColor(sf::Color(mShield_Color.r*Ratio, mShield_Color.g*Ratio, (mShield_Color.b/Ratio < 180) ? (mShield_Color.b/Ratio) : 180));
    mShieldBar.setSize(sf::Vector2f(Ratio*mShield_Dimensions.x, mShield_Dimensions.y));
}

void HudNode::setBackground(string PHudNode)
{
    mBackground_Texture->loadFromFile(PHudNode);
    this->setTexture(*Background_Texture);
}

void HudNode::setHealthBar(sf::Color Color, sf::Vector2f Size, sf::Vector2f Relative)
{
    mHealthBar.setFillColor(Color);
    mHealth_Color = Color;
    mHealth_Dimensions = Size;
    mHealth_RelativePos = Relative;
}

void HudNode::setShieldBar(sf::Color Color, sf::Vector2f Size, sf::Vector2f Relative)
{
    mShieldBar.setFillColor(Color);
    mShield_Color = Color;
    mShield_Dimensions = Size;
    mShield_RelativePos = Relative;
}

void HudNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*this);
    target.draw(mHealthBar, states);
    target.draw(mShieldBar, states);
}
