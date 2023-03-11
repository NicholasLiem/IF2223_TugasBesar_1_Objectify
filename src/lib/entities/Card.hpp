#ifndef __CARD_
#define __CARD_

#include "Valuable.hpp"

enum class CardColor { Green, Blue, Yellow, Red };
enum class CardNumber {
    One = 1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Eleven,
    Twelve,
    Thirteen
};

class Card : public Valuable
{
  public:
    Card(const CardColor color, const CardNumber number)
        : color(color), number(number){};
    Card(const Card& other) : Card(other.color, other.number) {}

    float value() const
    {
        return int(number) + int(color) * 0.003;
    }

    CardColor getColor() const
    {
        return color;
    }

    CardNumber getNumber() const
    {
        return number;
    }

    friend bool operator==(const Card& card1, const Card& card2)
    {
        return card1.value() == card2.value();
    }

    Card& operator=(const Card& other)
    {
        this->color = other.color;
        this->number = other.number;
        return *this;
    }

  private:
    CardColor color;
    CardNumber number;
};

#endif // !__CARD_
