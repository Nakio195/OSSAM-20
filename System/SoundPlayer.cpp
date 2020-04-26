#include "SoundPlayer.h"
#include "Ressources/RessourceIdentifiers.h"

#include <math.h>

namespace
{
    const float ListenerZ = 100.f;
    const float Attenuation  = 20.f;
    const float MinDistance2D = 200.f;
    const float minDistance3D = std::sqrt(MinDistance2D*MinDistance2D + ListenerZ*ListenerZ);
}

SoundPlayer::SoundPlayer() :
    mSounds(),
    mPlayingSounds()
{
    mSounds.load(Sounds::CP_Blast, "Ressources/Sounds/laser2.wav");
    mSounds.load(Sounds::ClassicExplode, "Ressources/Sounds/explosion.ogg");
}

void SoundPlayer::play(Sounds::ID effect)
{
    play(effect, getListnerPosition());
}
void SoundPlayer::play(Sounds::ID effect, sf::Vector2f position)
{
    mPlayingSounds.push_back(sf::Sound(mSounds.get(effect)));
    sf::Sound &sound = mPlayingSounds.back();

    sound.setPosition(position.x, position.y, 0.f);
    sound.setAttenuation(Attenuation);
    sound.setMinDistance(minDistance3D);

    sound.setVolume(1.f);
    sound.play();
}

void SoundPlayer::removeStoppedSounnds()
{
    mPlayingSounds.remove_if([] (const sf::Sound& s)
    {
        return s.getStatus() == sf::Sound::Stopped;
    });
}

void SoundPlayer::setListnerPosition(sf::Vector2f position)
{
    sf::Listener::setPosition(position.x, -position.y, ListenerZ);
}

sf::Vector2f SoundPlayer::getListnerPosition() const
{
    return sf::Vector2f(sf::Listener::getPosition().x, sf::Listener::getPosition().y);
}
