#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

#include <list>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Listener.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Ressources/RessourceHolder.h"
#include "Ressources/RessourceIdentifiers.h"

class SoundPlayer
{
    public:
        SoundPlayer();

        void play(Sounds::ID effect);
        void play(Sounds::ID effect, sf::Vector2f position);

        void removeStoppedSounnds();
        void setListnerPosition(sf::Vector2f position);
        sf::Vector2f getListnerPosition() const;

    private:
        SoundHolder mSounds;
        std::list<sf::Sound> mPlayingSounds;

};

#endif // SOUNDPLAYER_H
