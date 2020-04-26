#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() :
    mMusic(),
    mFilenames(),
    mVolume(50.f)
{
    mFilenames[Music::TitleTheme] = "Ressources/Music/title.ogg";
    mFilenames[Music::Level1] = "Ressources/Music/level1.ogg";
}


void MusicPlayer::play(Music::ID theme)
{
    std::string filename = mFilenames[theme];

    if(!mMusic.openFromFile(filename))
        throw std::runtime_error("Music " +filename + "could not be loaded from disk...");

    mMusic.setVolume(mVolume);
    mMusic.setLoop(true);
    mMusic.play();
}

void MusicPlayer::stop()
{
    mMusic.stop();
}

void MusicPlayer::setPause(bool paused)
{
    if(paused)
        mMusic.pause();
    else
        mMusic.play();
}

void MusicPlayer::setVolume(float volume)
{
    mMusic.setVolume(volume);
}
