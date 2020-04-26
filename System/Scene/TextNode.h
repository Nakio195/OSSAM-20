#ifndef TEXTNODE_H
#define TEXTNODE_H

#include <string>
#include "Ressources/RessourceIdentifiers.h"
#include "System/Scene/SceneNode.h"

class TextNode : public SceneNode
{
    public:
        explicit TextNode(const FontHolder& fonts, const std::string& text);
        void  setString(const std::string& text);

        virtual unsigned int getSceneCategory() const;

        void setCharacterSize(unsigned int size);

    private:
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        sf::Text mText;

};

#endif // TEXTNODE_H
