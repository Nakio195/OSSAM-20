#include "Item.h"
#include "System/UI/UI_Slot.h"
#include "Ressources/RessourceHolder.h"

Item::Item(std::string pName, const IconHolder &icons, Icons::ID icon) : mIcon(icons.get(icon))
{
    Name = pName;
    mType = Item::Passive;
    mState = Item::InBag;

    mOwner = nullptr;
    mSlot = nullptr;
}

void Item::setName(std::string pName)
{
    if(pName.empty() == false)
        Name = pName;
}

std::string Item::getName()
{
    return Name;
}

Item::State Item::getState()
{
    return mState;
}

void Item::setState(Item::State pState)
{
    if(pState == Item::InSpace || pState == Item::Equiped || pState == Item::InBag)
        mState = pState;
}

Item::Type Item::getType()
{
    return mType;
}
void Item::setType(Item::Type type)
{
    mType = type;
}

void Item::setOwner(Spaceship *newOwner)
{
    mOwner = newOwner;
}
void Item::setMySlot(UI_Slot* MyNewSlot)
{

}
