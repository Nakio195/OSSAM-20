#include "SoundNode.h"

SoundNode::SoundNode(SoundPlayer& player) : mSounds(player)
{
}


void SoundNode::playSound(Sounds::ID effect, sf::Vector2f position)
{
    mSounds.play(effect, position);
}

unsigned int SoundNode::getSceneCategory() const
{
    return Category::SoundNode;
}

