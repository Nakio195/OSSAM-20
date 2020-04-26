#ifndef SPRITENODE_H
#define SPRITENODE_H

#include <SFML/Graphics.hpp>
#include "System/Scene/SceneNode.h"

class SpriteNode : public SceneNode
{
    public:
        SpriteNode(const sf::Texture& texture);
        SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

    private:
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual unsigned int getSceneCategory() const;

    private:
        sf::Sprite mSprite;
};

#endif // SPRITENODE_H
