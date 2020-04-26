#ifndef TIMER_H
#define TIMER_H

namespace sf
{
    class Time;
}

class Timer
{
    public:
        enum Mode{OneShot = 0, Continuous};

    public:
        Timer(float pPeriod = 1, unsigned int pMode = 0);
        Timer(sf::Time pPeriod, unsigned int pMode = 0);

        bool isRunning() const;

        float getPeriod() const;
        void setPeriod(float pPeriod);
        void setPeriod(sf::Time pPeriod);

        float getCounter() const;
        void Count(float pElapsedTime);
        void Count(sf::Time pElapsedTime);

        bool Triggered();

        void StartTimer(float pPeriod = 0);  // Start Timer
        void PauseTimer();
        void ReleaseTimer();
        void StopTimer();                   // Stop

        unsigned int getMode() const;
        void setMode(unsigned int pMode);

        float getProgression() const;

    private:
        unsigned int mMode;  // Timer mode according to enum TimerMode
        bool mRunning;

        float mPeriod;       //Time till event trigger in s
        float mCounter;      //Elapsed time since start in s
        bool mTrigger;       //Event triggered
};

#endif // TIMER_H
