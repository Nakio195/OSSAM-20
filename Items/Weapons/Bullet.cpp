#include "Bullet.h"
#include "../../Entities/Spaceship.h"


/**
 * @brief Bullet::Bullet
 * @param pParent
 * @param pName
 * @param pHit
 * @param PathToBulletTexture
 * @param PathToBlastTexture
 */

Bullet::Bullet(Spaceship *pParent, string pName, unsigned int pHit, string PathToBulletTexture, string PathToBlastTexture) : Entity()
{
    setHit(pHit);
    setParent(pParent);
    Speed = 1500;
    BulletTexture = new sf::Texture();
    BulletTexture->loadFromFile(PathToBulletTexture);
    //ChangeTexture(BulletTexture);

    BlastTexture = new sf::Texture();
    BlastTexture->loadFromFile(PathToBlastTexture);
    BlastAnim = new Animation<Bullet>(this, 0.1, Animation<Bullet>::Sprite, BlastTexture);
    BlastAnim->setFrame(3, sf::IntRect(0, 0, 130, 140));
    BlastAnim->setOrigin(BlastAnim->getFrameRect().width/2, BlastAnim->getFrameRect().height/2);

    //setOrigin(getTexture()->getSize().x, getTexture()->getSize().y/2);

    Remove = false;
    Exploded = false;
}

bool Bullet::isBlastAnimRunning()
{
    return BlastAnim->isRunning();
}

bool Bullet::isExploded()
{
    return Exploded;
}

bool Bullet::NeedRemove()
{
    return Remove;
}

void Bullet::Move()
{
    //std::cout << "\t\tElapsed Time :" << ElapsedTime << std::endl;

    //if(ElapsedTime < 100.0 && ElapsedTime > 0.0)
    //    move(Speed*ElapsedTime*Direction.x, Speed*ElapsedTime*Direction.y);
}

Bullet::Bullet(Bullet *copy) : Entity()
{
    BlastAnim = new Animation<Bullet>(copy->BlastAnim);
    BlastAnim->setParent(this);
    BlastAnim->setStartAction(NULL);
    BlastAnim->setRepeatAction(NULL);
    BlastAnim->setEndAction(&Bullet::BlastAnim_EndAction);
    BlastAnim->setOrigin(0, BlastAnim->getFrameRect().height/2);

    Hit = copy->Hit;
    Direction = copy->Direction;
    Parent = copy->Parent;
    Speed = copy->Speed;
    BulletTexture = copy->BulletTexture;
    BlastTexture = copy->BlastTexture;
    Type = copy->Type;
    Remove = false;
    Exploded = false;
    //ChangeTexture(BulletTexture);
    //setOrigin(getTexture()->getSize().x/2, getTexture()->getSize().y/2);
}

Bullet::~Bullet()
{

}

unsigned int Bullet::getType()
{
    return Type;
}


void Bullet::Hitting(Spaceship *Shooter, Spaceship *Shooted)
{
    if(!Exploded)
    {
        //Shooted->takeDamage(this);
        if(Shooted->isDead())
            Exploded = true;

        //if(Shooted->getStats().life <= 0)
        //    Shooter->setAimedTarget(nullptr);

        BlastAnim->Start();
    }

    else if(Exploded && !BlastAnim->isRunning())
    {
        Remove = true;
    }
}


unsigned int Bullet::getHit()
{
    return Hit;
}

void Bullet::setHit(unsigned int pHit)
{
    Hit = pHit;
}

void Bullet::setBlastTexture(string Path)
{
    BlastTexture->loadFromFile(Path);
}

void Bullet::setBlastTexture(sf::Texture *pBlast)
{
    BulletTexture = pBlast;
}

void Bullet::setBulletTexture(string Path)
{
    BulletTexture->loadFromFile(Path);
}

void Bullet::setBulletTexture(sf::Texture *pBullet)
{
    BulletTexture = pBullet;
}

void Bullet::setSpeed(float pSpeed)
{
    Speed = pSpeed;
}

float Bullet::getSpeed()
{
    return Speed;
}


void Bullet::setParent(Spaceship *pParent)
{
    Parent = pParent;
}

Spaceship *Bullet::getParent()
{
    return Parent;
}

void Bullet::setDirection(sf::Vector2f pDirection)
{
    Direction = pDirection;
}

sf::Vector2f Bullet::getDirection()
{
    return Direction;
}

void Bullet::RefreshElapsedTime(bool Release)
{
    //Entity::RefreshElapsedTime(Release);
    //BlastAnim->Play(ElapsedTime);
}

void Bullet::draw(sf::RenderWindow *Window)
{
    if(BlastAnim->isRunning())
    {
        BlastAnim->setPosition(getPosition().x, getPosition().y);
        Window->draw(*BlastAnim);
    }

    else
        Window->draw(*this);
}

void Bullet::BlastAnim_EndAction()
{
    Remove = true;
}

