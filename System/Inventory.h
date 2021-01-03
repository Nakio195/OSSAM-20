    #ifndef INVENTORY_H
#define INVENTORY_H

#include <list>

#include <SFML/Graphics.hpp>
#include "UserInterface.h"
#include "Scene/UI/UI_Button.h"
#include "Scene/UI/UI_Slot.h"
#include "../Items/Weapons/Weapon.h"
#include "../Items/Shield.h"

#define BAG_SIZE    10

class Spaceship;
class Shield;

class Inventory : public UserInterface
{
    public:
        Inventory(const Spaceship& newOwner);
        void Display(sf::RenderWindow &Window);
        void HandleEvent(sf::Event &Event);
        bool addItem(Item *NewItem);
        bool useItem(Item *ItemToUse, unsigned int Parameter = 255);
        void selectTab(unsigned int Category);
        bool OwnerNeedRefresh();
        void OwnerRefreshed();

        Weapon* getWeaponItem(unsigned int Type);
        Shield* getShieldItem();

        bool isOpened();
        void Close();
        void Open();

    private:
        bool Opened;
        Spaceship *Owner;
        bool RefreshOwner;

        sf::Texture Background;
        sf::Font TextFont;
        sf::Text CategoryTxt;

        UI_Slot* Slot_MainWeapon;
        UI_Slot* Slot_SecondaryWeapon;
        UI_Slot* Slot_MainShield;
        UI_Slot* Slot_MainBumper;
        UI_Slot* MyBag[BAG_SIZE];

        UI_Button *CloseBtn;
        UI_Button *NextBtn;
        UI_Button *PreviousBtn;

        unsigned int CurrentTab;

        std::list<Weapon*> MyWeapons;
        std::list<Shield*> MyShields;
        std::list<Shield*> MyPowerUp;

        Weapon *MainWeapon;
        Weapon *SecondaryWeapon;

        Shield *MainShield;


};

#endif // INVENTORY_H
