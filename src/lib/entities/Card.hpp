#ifndef __CARD_
#define __CARD_

#include "Valuable.hpp"

#include <istream>
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

enum class CardSymbol { Diamond, Club, Heart, Spade };

enum class CangkulNumber {
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
    Fourteen = 14,
};

std::ostream& operator<<(std::ostream& out, const CardColor& color);
std::ostream& operator<<(std::ostream& out, const CardNumber& number);
std::ostream& operator<<(std::ostream& out, const CardSymbol& symbol);
std::ostream& operator<<(std::ostream& out, const CangkulNumber& number);

template <class T, class U>
class Card : public Valuable
{
  public:
    Card(const T color, const U number);
    Card(const int color, const int number);
    Card(const Card<T, U>& other);

    float value() const;
    T getColor() const;

    U getNumber() const;

    Card<T, U>& operator=(const Card<T, U>& other);

    bool operator==(const Card<T, U>& other);

    friend bool operator==(const Card<T, U>& card1, const Card<T, U>& card2)
    {
        return card1.getNumber() == card2.getNumber();
    }

    friend bool operator<(const Card<T, U>& card1, const Card<T, U>& card2)
    {
        return card1.value() < card2.value();
    }

    friend bool operator>(const Card<T, U>& card1, const Card<T, U>& card2)
    {
        return card1.value() > card2.value();
    }

    friend std::ostream& operator<<(std::ostream& out, const Card<T, U>& card)
    {
        out << card.getNumber() << " " << card.getColor();
        return out;
    }

    friend std::ostream&
    operator<<(std::ostream& os, const Card<CardSymbol, CangkulNumber>& card);

    friend istream& operator>>(istream& in, Card<CardColor, CardNumber>& card);

  private:
    T color;
    U number;
};

typedef Card<CardColor, CardNumber> MainCard;
typedef Card<CardSymbol, CangkulNumber> CangkulCard;

#endif // !__CARD_
