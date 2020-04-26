#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <map>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>
#include "Ressources/RessourceIdentifiers.h"

class MusicPlayer : private sf::NonCopyable
{
    public:
        MusicPlayer();

        void play(Music::ID theme);
        void stop();
        void setVolume(float volume);
        void setPause(bool paused);

    private:
        sf::Music mMusic;
        std::map<Music::ID, std::string> mFilenames;
        float mVolume;
};

#endif // MUSICPLAYER_H
