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

enum class CardSymbol{ Diamond, Club, Heart, Spade };

enum class CangkulNumber{
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

template <class T, class U>
class Card : public Valuable
{
  public:
    Card(const T color, const U number);
    Card(const int color, const int number);
    Card(const Card<T,U>& other);

    float value() const;
    T getColor() const;

    U getNumber() const;
  
    Card<T,U>& operator=(const Card<T,U>& other);

    bool operator==(const Card<T,U>& other);

    template <class T2,class U2>
    friend bool operator==(const Card<T2,U2>& card1, const Card<T2,U2>& card2);
    friend bool operator==(const Card<CardColor,CardNumber>& card1, const Card<CardColor,CardNumber>& card2);


    template <class T2,class U2>
    friend bool operator<(const Card<T2,U2>& card1, const Card<T2,U2>& card2);
    friend bool operator<(const Card<CardColor,CardNumber>& card1, const Card<CardColor,CardNumber>& card2);


    template <class T2,class U2>
    friend bool operator>(const Card<T2,U2>& card1, const Card<T2,U2>& card2);
    friend bool operator>(const Card<CardColor,CardNumber>& card1, const Card<CardColor,CardNumber>& card2);


    template <class T2,class U2>
    friend std::ostream& operator<<(std::ostream& out, const Card<T2,U2>& card);
    friend std::ostream& operator<<(std::ostream& out, const Card<CardColor,CardNumber>& card);

  private:
    T color;
    U number;
};

#endif // !__CARD_
