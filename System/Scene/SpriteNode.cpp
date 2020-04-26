#include "System/Scene/SpriteNode.h"


SpriteNode::SpriteNode(const sf::Texture& texture) : mSprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect) : mSprite(texture, textureRect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}


unsigned int SpriteNode::getSceneCategory() const
{
    return Category::SpriteNode;
}
