#include "Shield.h"

#include "Entities/DataTables.h"
#include "Ressources/RessourceHolder.h"
/**
 * @brief Shield::Shield
 * @param pParent
 * @param Shield
 * @param pName
 */


namespace
{
    const std::vector<ShieldData> Table = initShields();
}



Shield::Shield(Shield::Type type, const TextureHolder& textures, const IconHolder& icons) : Item(Table[type].name, icons, Table[type].icon)
{
    Item::setType(Item::Shield);

    mShieldMax = Table[type].shield;
    mShieldPoints = mShieldMax;

    Hitmark.setPeriod(0.3f);
    Hitmark.setMode(Timer::OneShot);
    Hitted = 0;

    ReloadTimer.setMode(Timer::Continuous);
    ReloadTimer.setPeriod(0.2f);
    ReloadTimer.StartTimer();

    CooldownTimer.setMode(Timer::OneShot);

    Texture_Shield = new sf::Texture();
    Texture_Broken = new sf::Texture();
}


int Shield::getShieldPoints()
{
    if(mShieldPoints > 0)
        return mShieldPoints;
    else
        return 0;
}


int Shield::getShieldMax()
{
    return mShieldMax;
}

int Shield::TakeDamage(const Projectile& Damage)
{
    int ExtraDamage = 0;

    if(mShieldMax == 0)
        return Damage.getDamage();

    if((mShieldPoints - int(Damage.getDamage())) < 0)
    {
        ExtraDamage = Damage.getDamage() - mShieldPoints;
        mShieldPoints = 0;

        Broken = true;
        Hitted = false;
        Hitmark.StopTimer();

        MainSprite.setTexture(*Texture_Broken);

        if(!CooldownTimer.isRunning())
        {
            CooldownTimer.StartTimer(3.0f);
            Hitted = true;
            Hitmark.StartTimer(0.4f);
            ExtraDamage = 0;
        }

    }

    else
    {
        mShieldPoints -= Damage.getDamage();
        Hitmark.StartTimer(0.8f);
        Hitted = true;
    }

    return ExtraDamage;
}

void Shield::RefreshElapsedTime(bool Release)
{
//    Item::RefreshElapsedTime(Release);

//    ReloadTimer.Count(ElapsedTime);
//    Hitmark.Count(ElapsedTime);
//    CooldownTimer.Count(ElapsedTime);

//    if(CooldownTimer.Triggered())
//    {
//        MainSprite.setTexture(*Texture_Shield);
//        Broken = false;
//    }

//    if(Hitmark.Triggered())
//        Hitted = false;

//    if(ReloadTimer.Triggered() && !Broken)
//    {
//        if(ShieldPoints < ShieldMax)
//            ShieldPoints ++;
//    }

}

sf::Vector2f Shield::getRelativePosition()
{
    return RelativePosition;
}

void Shield::setShieldTexture(sf::Texture *Texture)
{
    Texture_Shield = Texture;
    MainSprite.setTexture(*Texture_Shield);
}

void Shield::setShieldTexture(std::string PathShield, string PathBroken)
{
    if(PathBroken == string(""))
        PathBroken = PathShield;

    Texture_Broken->loadFromFile(PathBroken);
    Texture_Shield->loadFromFile(PathShield);

    MainSprite.setTexture(*Texture_Shield);
    MainSprite.setOrigin(MainSprite.getTexture()->getSize().x/2, MainSprite.getTexture()->getSize().y/2);

}

void Shield::draw(sf::RenderWindow *Window)
{
    MainSprite.setPosition(Parent->getPosition()+RelativePosition);

    if(Hitted)
        Window->draw(MainSprite);
}

