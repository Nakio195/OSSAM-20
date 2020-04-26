#ifndef RESSOURCEIDIENTIFIERS_H
#define RESSOURCEIDIENTIFIERS_H

namespace sf
{
    class Texture;
    class Font;
    class SoundBuffer;
}

namespace Textures
{
    enum ID
    {
        Khaal,
        Intercepter,
        Blade,

        SpaceshipDebris,
        AsteroidDebris,

        Khaal_Explode,
        Classic_Explode,

        Planet1,

        SpaceLvl1,

        Bullet,
        Missile,
        Particle,
        LaserBlue,
        LaserBlue_Fire,
        LaserRed,
        LaserGun,

        TitleScreen,
        TitleScreen2,
        TexturesCount
    };
}

namespace Icons
{
    enum ID
    {
        Laser1,
        Laser2,
        Laser3,
        Pouclier
    };
}

namespace Fonts
{
    enum ID
    {
        Main,
        KLM
    };
}


namespace Music
{
    enum ID
    {
        TitleTheme,
        Level1
    };
}

namespace Sounds
{
    enum ID
    {
        CP_Blast,
        ClassicExplode,
        SoundsCount
    };
}


template <typename Ressource, typename Identifier>
class RessourceHolder;

typedef RessourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef RessourceHolder<sf::Texture, Icons::ID> IconHolder;
typedef RessourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef RessourceHolder<sf::SoundBuffer, Sounds::ID> SoundHolder;


#endif // RESSOURCEIDIENTIFIERS_H
