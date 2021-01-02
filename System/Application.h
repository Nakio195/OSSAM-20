#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Ressources/RessourceHolder.h"
#include "Ressources/RessourceIdentifiers.h"
#include "System/SoundPlayer.h"
#include "System/MusicPlayer.h"
#include "System/States/StateStack.h"
#include "Player.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
    public:
        Application();
        void run();

    private:
        void processInput();
        void update(sf::Time dt);
        void render();

        void registerStates();

    private:
        static const sf::Time TimePerFrame;

        sf::RenderWindow mWindow;
        TextureHolder mTextures;
        FontHolder mFonts;
        SoundPlayer mSoundPlayer;
        MusicPlayer mMusicPlayer;
        Player mPlayer;

        StateStack mStateStack;
};

#endif // BOOK_APPLICATION_HPP
