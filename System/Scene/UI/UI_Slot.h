#ifndef UI_SLOT_H
#define UI_SLOT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "../../UserInterface.h"
#include "../../../Items/Item.h"

class UI_Slot : public UserInterface
{
    public:
        enum States{Enabled, Disabled, Clicked, Dragged, Accept, Reject};
        enum Types{Bag = Item::Passive, Weapon = Item::Weapon, Shield = Item::Shield, Bumper = Item::Bumper};

    public:
        UI_Slot(UserInterface *pParent, unsigned int pType);

        bool isDropped();
        bool isHovered();
        bool isEmpty();

        void setState(unsigned int pState);
        unsigned int getState();

        void Clear();
        void setType(unsigned int pType);
        unsigned int getType();
        void setItem(Item* pItem);
        Item* getItem();

        void setIcon(sf::Texture* pTexture);

        void setRelativePosition(float x, float y);
        void setRelativePosition(sf::Vector2f RelativePosition);
        sf::Vector2f getRelativePosition();
        sf::Vector2f getDropPosition();

        void ValidateDrop();
        void UnvalidateDrop();

        void Display(sf::RenderWindow &Window);
        void HandleEvent(sf::Event &Event);

    private:
        UserInterface *Parent;

        unsigned int Type;

        sf::Texture *Background;

        sf::Sprite Icon;
        sf::Texture *TextureIcon;

        sf::Vector2f Position;
        sf::Vector2f Origin;
        sf::Vector2f DragStartPosition;
        sf::Vector2f DropPlace;
        unsigned int State;
        unsigned int OldState;
        bool Dropped;
        bool Hovered;
        bool Empty;

        Item *Container;

};

#endif // UI_SLOT_H
