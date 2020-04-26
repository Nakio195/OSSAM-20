#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

#include "Entities/Entity.h"
#include "Ressources/RessourceHolder.h"
#include "Ressources/RessourceIdentifiers.h"

class Spaceship;
class UI_Slot;

class Item
{
    public:
        enum Type{Weapon, Shield, PowerUp, Bumper, Passive};
        enum State{InSpace, InBag, Equiped};

    public:
        Item(std::string pName, const IconHolder& icons, Icons::ID icon);
        void setName(std::string pName);
        std::string getName();

        Item::Type getType();

        Item::State getState();
        void setState(Item::State pState);

        void setOwner(Spaceship *newOwner);
        void setMySlot(UI_Slot* MyNewSlot);

        void setIcon(Icons::ID icon);

    protected:
        void setType(Item::Type pType);

    private:
        UI_Slot *mSlot;
        Spaceship *mOwner;

        std::string Name;
        Item::Type mType;

        sf::Sprite mIcon;

        Item::State mState;
};


#endif // ITEM_H
