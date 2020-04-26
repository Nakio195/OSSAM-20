#ifndef ANIMATIONNODE_H
#define ANIMATIONNODE_H

#include "System/Scene/SceneNode.h"
#include "System/Animation.h"

class AnimationNode : public SceneNode
{
    public:
        AnimationNode(Animation::Type type, const TextureHolder &textures);

        virtual unsigned int getSceneCategory() const override;

        Animation& getAnimation();

    private:
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void updateCurrent(sf::Time dt, CommandQueue &Commands) override;

    private:
        Animation mAnim;
};

#endif // ANIMATIONNODE_H
