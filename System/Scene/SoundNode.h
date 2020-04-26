#ifndef SOUNDNODE_H
#define SOUNDNODE_H

#include "System/SoundPlayer.h"
#include "System/Scene/SceneNode.h"
#include "Ressources/RessourceIdentifiers.h"

class SoundNode : public SceneNode
{
    public:
        SoundNode(SoundPlayer& player);

        void playSound(Sounds::ID effect, sf::Vector2f position);

        virtual unsigned int getSceneCategory() const override;

    private:
        SoundPlayer& mSounds;

};

#endif // SOUNDNODE_H
