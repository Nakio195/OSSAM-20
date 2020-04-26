#ifndef PARTICLENODE_H
#define PARTICLENODE_H

#include "System/Scene/SceneNode.h"
#include "System/Scene/Particle.h"
#include "Ressources/RessourceIdentifiers.h"

class ParticleNode : public SceneNode
{
    public:
        ParticleNode(Particle::Type type, const TextureHolder& textures);

        void addParticle(sf::Vector2f positioon);
        Particle::Type getParticleType() const;
        virtual unsigned int getCategory() const;

    private:
        virtual void updateCurrent(sf::Time dt, CommandQueue& commands);
        virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

        void addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const;
        void computeVertices() const;

    private:
        std::deque<Particle> mParticles;
        const sf::Texture& mTexture;
        Particle::Type mType;

        mutable sf::VertexArray mVertexArray;
        mutable bool mNeedsVertexUpdate;
};

#endif // PARTICLENODE_H
