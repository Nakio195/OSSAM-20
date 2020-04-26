#include "TextNode.h"
#include "Ressources/RessourceHolder.h"
#include "System/Utilities.h"

TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
    mText.setFont(fonts.get(Fonts::KLM));
    mText.setCharacterSize(20);
    setString(text);
}

void  TextNode::setString(const std::string& text)
{
    mText.setString(text);
    centerOrigin(mText);
}


void TextNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mText, states);
}

unsigned int TextNode::getSceneCategory() const
{
    return Category::TextNode;
}

void TextNode::setCharacterSize(unsigned int size)
{
    mText.setCharacterSize(size);
}
