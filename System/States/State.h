#ifndef STATE_H
#define STATE_H

#include "StateIdentifiers.h"
#include "Ressources/RessourceIdentifiers.h"
#include "System/SoundPlayer.h"
#include "System/MusicPlayer.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <memory>


namespace sf
{
    class RenderWindow;
}

class StateStack;
class Player;

class State
{
    public:
        typedef std::unique_ptr<State> ptr;

        struct Context
        {
            Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player, MusicPlayer &musicPlayer, SoundPlayer& soundPlayer);

            sf::RenderWindow*	window;
            TextureHolder*		textures;
            FontHolder*			fonts;
            Player*				player;
            MusicPlayer*        musicPlayer;
            SoundPlayer*        soundPlayer;
        };

    public:
        explicit State(StateStack& stack, Context context);
        virtual ~State();

        virtual void draw() = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual bool handleEvent(const sf::Event &event) = 0;

    protected:
        void requestStackPush(States::ID stateID);
        void requestStackPop();
        void requestStateClear();

        Context getContext() const;

    private:
        StateStack* mStack;
        Context mContext;
};

#endif // STATE_H
