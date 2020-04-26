#include "AnimationNode.h"

AnimationNode::AnimationNode(Animation::Type type, const TextureHolder& textures) :
    mAnim(type, textures)
{
}

void AnimationNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    mAnim.draw(target, states);
}

void AnimationNode::updateCurrent(sf::Time dt, CommandQueue &Commands)
{
    mAnim.play(dt, Commands);
}

unsigned int AnimationNode::getSceneCategory() const
{
    return Category::AnimationNode;
}


Animation& AnimationNode::getAnimation()
{
    return mAnim;
}
