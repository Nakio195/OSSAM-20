#include "UI_Slot.h"

/**
 * @brief UI_Slot::UI_Slot
 * @param pParent
 * @param pType
 */

UI_Slot::UI_Slot(UserInterface *pParent, unsigned int pType) : UserInterface()
{
    Background = new sf::Texture();

    if(Background->loadFromFile("Ressources/System/Icon/Empty.png"))
        sf::Sprite::setTexture(*Background);

    TextureIcon = new sf::Texture();

    Parent = pParent;

    State = UI_Slot::Enabled;
    OldState = State;
    Dropped = false;
    Empty = true;
    Type = pType;
    Hovered = false;
}

void UI_Slot::setType(unsigned int pType)
{
    switch(pType)
    {
        case UI_Slot::Bag || UI_Slot::Bumper || UI_Slot::Weapon || UI_Slot::Shield:
            Type = pType;
            break;
    }
}

unsigned int UI_Slot::getType()
{
    return Type;
}

sf::Vector2f UI_Slot::getDropPosition()
{
    if(Dropped)
    {
        Position = Origin;
        return DropPlace;
    }

    else
        return sf::Vector2f();
}

bool UI_Slot::isDropped()
{
    return Dropped;
}

void UI_Slot::ValidateDrop()
{
    Dropped = false;
    DropPlace = sf::Vector2f();
    setState(UI_Slot::Enabled);
}

void UI_Slot::UnvalidateDrop()
{
    Dropped = false;
    Position = Origin;
    DropPlace = sf::Vector2f();
    setState(UI_Slot::Enabled);
}

bool UI_Slot::isHovered()
{
    return Hovered;
}

bool UI_Slot::isEmpty()
{
    return Empty;
}


void UI_Slot::Clear()
{
    Container = nullptr;
    setTexture(*Background);
    Empty = true;
}

void UI_Slot::setItem(Item* pItem)
{
    Container = pItem;
    //setIcon(pItem->getIcon());
    Empty = false;
}

Item* UI_Slot::getItem()
{
    if(!Empty)
        return Container;
}

void UI_Slot::setIcon(sf::Texture* pTexture)
{
    TextureIcon = pTexture;
    Icon.setTexture(*pTexture);
}

void UI_Slot::setState(unsigned int pState)
{
    if(pState == UI_Slot::Enabled)
    {
        setColor(sf::Color(0xFF, 0xFF, 0xFF));
        Icon.setColor(sf::Color(0xFF, 0xFF, 0xFF));
        State = pState;
    }

    else if(pState == UI_Slot::Disabled)
    {
        Icon.setColor(sf::Color(0x80, 0x80, 0x80));
        State = pState;
    }

    else if(pState == UI_Slot::Clicked)
    {
        Icon.setColor(sf::Color(0x80, 0xFF, 0x80));
        State = pState;
    }

    else if(pState == UI_Slot::Dragged)
    {
        Icon.setColor(sf::Color(0xFF, 0xFF, 0xFF, 0xA0));
        State = pState;
    }

    else if(pState == UI_Slot::Accept)
    {
        setColor(sf::Color(0x80, 0xFF, 0x80));
        if(State != UI_Slot::Accept && State != UI_Slot::Reject)
        {
            OldState = State;
            State = pState;
        }
    }

    else if(pState == UI_Slot::Reject)
    {
        setColor(sf::Color(0xFF, 0x00, 0x00));
        if(State != UI_Slot::Accept && State != UI_Slot::Reject)
        {
            OldState = State;
            State = pState;
        }
    }
}


unsigned int UI_Slot::getState()
{
    return State;
}

void UI_Slot::setRelativePosition(float x, float y)
{
    Position = sf::Vector2f(x, y);
    Origin = Position;
}

void UI_Slot::setRelativePosition(sf::Vector2f RelativePosition)
{
    Position = RelativePosition;
    Origin = Position;
}

sf::Vector2f UI_Slot::getRelativePosition()
{
    return Position;
}

void UI_Slot::Display(sf::RenderWindow &Window)
{
    setPosition(Parent->getPosition() + Origin);
    Icon.setPosition(Parent->getPosition() + Position);
    Window.draw(*this);

    if(!Empty)
        Window.draw(Icon);
}

void UI_Slot::HandleEvent(sf::Event &Event)
{
    if(State == UI_Slot::Disabled)
        return;

    switch(Event.type)
    {
        case sf::Event::MouseButtonPressed:
            if(Event.mouseButton.button == sf::Mouse::Left)
            {
                if(this->getGlobalBounds().contains(Event.mouseButton.x, Event.mouseButton.y) && !Empty)
                {
                    setState(UI_Slot::Dragged);
                    DragStartPosition = sf::Vector2f(Event.mouseButton.x, Event.mouseButton.y);
                    //Icon.setOrigin(Icon.getTexture()->getSize().x/2, Icon.getTexture()->getSize().y/2);
                    Icon.setPosition(Event.mouseButton.x, Event.mouseButton.y);
                }
            }
            break;

        case sf::Event::MouseButtonReleased:
            if(Event.mouseButton.button == sf::Mouse::Left)
            {
                if(State == UI_Slot::Dragged)
                {
                    setState(UI_Slot::Enabled);
                    Dropped = true;
                    DropPlace = sf::Vector2f(Event.mouseButton.x, Event.mouseButton.y);
                }
            }
            break;

        case sf::Event::MouseMoved:
            if(this->getGlobalBounds().contains(sf::Vector2f(Event.mouseMove.x, Event.mouseMove.y)))
                Hovered = true;

            else
            {
                Hovered = false;
                if(State == UI_Slot::Accept || State == UI_Slot::Reject)
                    setState(OldState);
            }

            if(State == UI_Slot::Dragged)
            {
                Position += sf::Vector2f(Event.mouseMove.x, Event.mouseMove.y) - DragStartPosition;
                DragStartPosition = sf::Vector2f(Event.mouseMove.x, Event.mouseMove.y);
            }
            break;

        default:
            break;
    }
}
