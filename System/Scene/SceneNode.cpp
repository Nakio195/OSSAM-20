#include "System/Scene/SceneNode.h"
#include <iostream>
#include "System/Utilities.h"


unsigned long SceneNode::UniqueSceneID = 1;

SceneNode::SceneNode(Category::Type categorie) : Drawable(), Transformable(), NonCopyable(), mDefaultCategory(categorie), mID(UniqueSceneID)
{
    mParent = nullptr;
    mNeedRemove = false;
    UniqueSceneID ++;
}

void SceneNode::attachChild(SceneNode::ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
    mSceneGraphChanged = true;
}

SceneNode::ptr SceneNode::detachChild(const SceneNode& child)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&] (SceneNode::ptr& p) -> bool {return p.get() == &child; });

    assert(found != mChildren.end());

    SceneNode::ptr result = std::move(*found);
    mChildren.erase(found);
    mSceneGraphChanged = true;
    return result;
}

bool SceneNode::isSceneGraphChanged()
{
    if(mSceneGraphChanged)
    {
        mSceneGraphChanged = false;
        return true;
    }

    else
    {
        for(auto& child : mChildren)
        {
            if(child->isSceneGraphChanged())
                return true;
        }

        return false;
    }
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target, states);

    for(const SceneNode::ptr &child : mChildren)
    {
        child->draw(target, states);
    }

    drawBoundingRect(target, states);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
    sf::FloatRect rect = getBoundingRect();

    sf::RectangleShape shape;
    shape.setPosition(sf::Vector2f(rect.left, rect.top));
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green);
    shape.setOutlineThickness(1.f);

    target.draw(shape);
}

void SceneNode::drawCurrent(sf::RenderTarget &, sf::RenderStates ) const
{

}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->mParent)
        transform = node->getTransform() * transform;

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

void SceneNode::update(sf::Time dt, CommandQueue& Commands)
{
    updateCurrent(dt, Commands);
    updateChildren(dt, Commands);
}

void SceneNode::updateCurrent(sf::Time , CommandQueue& )
{

}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& Commands)
{
    for(SceneNode::ptr &child : mChildren)
    {
        child->update(dt, Commands);
    }
}

void SceneNode::printSceneGraph(unsigned int level)
{

    for(unsigned int i = 0; i < level; i++)
        std::cout << "\t";

    std::cout << "--> ";

    std::string CatText;
    unsigned int cat = getSceneCategory();

    if(cat & Category::PlayerSpaceship) { CatText += "PlayerSpaceship "; }
    else if(cat & Category::EnemySpaceship) { CatText += "EnemySpaceship "; }
    else if(cat & Category::AlliedSpaceship) { CatText += "AlliedSpaceship "; }
    if(cat & Category::SceneProjectileLayer) { CatText += "SceneProjectileLayer "; }
    if(cat & Category::SceneAirLayer) { CatText += "SceneAirLayer "; }
    if(cat & Category::SceneBackgroundLayer) { CatText += "SceneBackgroundLayer "; }
    if(cat & Category::EnemyProjectile) { CatText += "EnemyProjectile "; }
    if(cat & Category::AlliedProjectile) { CatText += "AlliedProjectile "; }
    if(cat & Category::None) { CatText += "None "; }
    if(cat & Category::Scene) { CatText += "Scene "; }
    if(cat & Category::Particle) { CatText += "Particle "; }
    if(cat & Category::Emitter) { CatText += "Emitter "; }
    if(cat & Category::TextNode) { CatText += "TextNode "; }
    if(cat & Category::SpriteNode) { CatText += "SpriteNode "; }
    if(cat & Category::Weapon) { CatText += "WeaponNode "; }

    if(CatText.empty())
        CatText += toString(cat);

    std::cout << CatText << std::endl;

    for(SceneNode::ptr &child : mChildren)
        child->printSceneGraph(level+1);
}

void SceneNode::onCommand(const Command& command, sf::Time dt)
{
    if(command.category & getSceneCategory())
    {
        if(command.id)
        {
            if(command.id == this->mID)
                command.action(*this, dt);
        }

        else
            command.action(*this, dt);
    }

    for(SceneNode::ptr& child : mChildren)
    {
        child->onCommand(command, dt);
    }
}

unsigned int SceneNode::getSceneCategory() const
{
    return mDefaultCategory;
}

sf::FloatRect SceneNode::getBoundingRect() const
{
    return sf::FloatRect();
}

void SceneNode::destroy()
{
    mNeedRemove = true;
}

bool SceneNode::needRemove() const
{
    return mNeedRemove;
}

bool SceneNode::isDead() const
{
    return false;
}

void SceneNode::cleanSceneGraph()
{
    // Remove all children which request so
    auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::needRemove));
    mChildren.erase(wreckfieldBegin, mChildren.end());

    for(SceneNode::ptr& child : mChildren)
    {
        child->cleanSceneGraph();
    }
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<pair>& collisionPairs)
{
    checkNodeCollision(sceneGraph, collisionPairs);

    for(SceneNode::ptr& child : sceneGraph.mChildren)
        checkSceneCollision(*child, collisionPairs);
}

void SceneNode::checkNodeCollision(SceneNode& node, std::set<pair>& collisionPairs)
{
    if (this != &node && collision(*this, node) && !isDead() && !node.isDead())
        collisionPairs.insert(std::minmax(this, &node));

    for(SceneNode::ptr& child : mChildren)
        child->checkNodeCollision(node, collisionPairs);
}

unsigned long SceneNode::getID()
{
    return mID;
}


bool collision(const SceneNode& lhs, const SceneNode& rhs)
{
    return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

