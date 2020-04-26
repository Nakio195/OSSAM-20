#ifndef UTILITIES_H
#define UTILITIES_H
#include <string>
#include <sstream>
#include <random>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf
{
    class Sprite;
    class Text;
}

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

std::string		toString(sf::Keyboard::Key key);

sf::Vector2f    saturateVector(sf::Vector2f vector, float threshold);

void			centerOrigin(sf::Sprite& sprite);
void			centerOrigin(sf::Text& text);

float			toDegree(float radian);
float			toRadian(float degree);

float           getAngle(sf::Vector2f vector);

int				randomInt(int exclusiveMax);

sf::Vector2f    rotateVector(sf::Vector2f base, float theta);
sf::Vector2f    fromAngle(float theta);
float			length(sf::Vector2f vector);
sf::Vector2f	unitVector(sf::Vector2f vector);
float			toDegree(float radian);
float			toRadian(float degree);

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

struct randomFloat
{
    randomFloat() : rd(), gen(rd()), min(0.f), max(1.f)
    {}

    float operator() (void)
    {
        return dist(gen);
    }

    void setRange(float Min, float Max)
    {
        min = Min;
        max = Max;
        dist = std::uniform_real_distribution<float>(Min, Max);
    }

    std::random_device rd;
    std::mt19937 gen;

    float min;
    float max;
    std::uniform_real_distribution<float> dist;
};

#endif // UTILITIES_H
