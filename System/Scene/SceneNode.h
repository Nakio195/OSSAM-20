#ifndef SCENENODE_H
#define SCENENODE_H

#include <memory>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <set>

#include <SFML/Graphics.hpp>
#include "System/Commands/Category.h"
#include "System/Commands/Command.h"

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> ptr;
        typedef std::pair<SceneNode*, SceneNode*> pair;

    public:
        SceneNode(Category::Type category = Category::Uninitialized);
        void attachChild(SceneNode::ptr child);
        SceneNode::ptr detachChild(const SceneNode& child);

        sf::Transform getWorldTransform() const;
        sf::Vector2f getWorldPosition() const;

        void onCommand(const Command& command, sf::Time dt);

        void update(sf::Time dt, CommandQueue& commands);

        void printSceneGraph(unsigned int level = 0);
        bool isSceneGraphChanged();

        virtual bool isDead() const;
        virtual bool needRemove() const;
        virtual void destroy();
        virtual unsigned int getSceneCategory() const;
        virtual sf::FloatRect getBoundingRect() const;

        void cleanSceneGraph();

        void checkSceneCollision(SceneNode& sceneGraph, std::set<pair>& collisionPairs);
        void checkNodeCollision(SceneNode& node, std::set<pair>& collisionPairs);

        unsigned long getID();

    protected:
        unsigned int mDefaultCategory;
        bool mNeedRemove;
        static unsigned long UniqueSceneID;

    private:
        virtual void updateCurrent(sf::Time dt, CommandQueue&);
        void updateChildren(sf::Time dt, CommandQueue& Commands);

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;

        virtual void drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const;

    private:
        std::vector<SceneNode::ptr> mChildren;
        SceneNode* mParent;

        bool mSceneGraphChanged;

        const unsigned long mID;

};


bool collision(const SceneNode& lhs, const SceneNode& rhs);



#endif // SCENENODE_H
