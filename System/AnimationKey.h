#ifndef ANIMATIONKEY
#define ANIMATIONKEY

#include <SFML/Graphics.hpp>

class AnimationKey
{
    public:
        enum Type{Rotation, Translation, Scale};
        enum RotationDir{Clockwise, CounterClockwise};
        enum Status{Stopped, Running, Finished};

    public:
        AnimationKey(unsigned int pMode, float pDuration);

        unsigned int getStatus();
        float getCompletion();

        void start();
        void play(sf::Time ElapsedTime);
        virtual void update();
        void stop();

    protected:
        float Duration;
        unsigned int Mode;
        unsigned int Status;

        float Completion;
        float Timer;
};

#endif // ANIMATIONKEY
