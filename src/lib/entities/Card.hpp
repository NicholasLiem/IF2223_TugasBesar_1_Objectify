#ifndef __CARD_
#define __CARD_

#include "Valuable.hpp"

#include <ostream>

enum class CardColor { Green, Blue, Yellow, Red };
enum class CardNumber {
    One = 1,
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7,
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Eleven = 11,
    Twelve = 12,
    Thirteen = 13,
};

class Card : public Valuable
{
  public:
    Card(const CardColor color, const CardNumber number);
    Card(const int color, const int number);
    Card(const Card& other);

    float value() const;
    CardColor getColor() const;

    CardNumber getNumber() const;
    Card& operator=(const Card& other);

    friend bool operator==(const Card& card1, const Card& card2);

    friend bool operator<(const Card& card1, const Card& card2);

    friend bool operator>(const Card& card1, const Card& card2);

    friend std::ostream& operator<<(const std::ostream& out, const Card& card);

  private:
    CardColor color;
    CardNumber number;
};

#endif // !__CARD_
