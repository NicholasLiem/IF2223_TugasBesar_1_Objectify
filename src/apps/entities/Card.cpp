#include "../../lib/entities/Card.hpp"

#include <iostream>
using namespace std;

template <class T, class U>
Card<T,U>::Card(const T color, const U number)
{
    this->color = color;
    this->number = number;
}

template <class T, class U>
Card<T,U>::Card(const int color, const int number)
{
    this->color = static_cast<T>(color);
    this->number = static_cast<U>(number);
}


template <class T, class U>
Card<T,U>::Card(const Card<T,U>& other)
{
    this->color = other.color;
    this->number = other.number;
}


template <class T, class U>
float Card<T,U>::value() const
{
    return int(number) + int(color) * 0.03;
}

template <class T, class U>
T Card<T,U>::getColor() const
{
    return color;
}

template <class T, class U>
U Card<T,U>::getNumber() const
{
    return number;
}

template <class T, class U>
bool Card<T,U>::operator==(const Card& card1){
    return (this->getNumber() == card1.getNumber());
}

template <class T, class U>
bool operator==(const Card<T,U>& card1, const Card<T,U>& card2)
{
    return (card1.getNumber() == card2.getNumber());
}

bool operator==(const Card<CardColor,CardNumber>& card1, const Card<CardColor,CardNumber>& card2)
{
    return (card1.getNumber() == card2.getNumber());
}

template <class T, class U>
Card<T,U>& Card<T,U>::operator=(const Card<T,U>& other)
{
    this->color = other.color;
    this->number = other.number;
    return *this;
}

template <class T, class U>
bool operator<(const Card<T,U>& card1, const Card<T,U>& card2)
{
    return (card1.value() < card2.value());
}

bool operator<(const Card<CardColor,CardNumber>& card1, const Card<CardColor,CardNumber>& card2)
{
    return (card1.value() < card2.value());
}

template <class T, class U>
bool operator>(const Card<T,U>& card1, const Card<T,U>& card2)
{
    return (card1.value() > card2.value());
}

bool operator>(const Card<CardColor,CardNumber>& card1, const Card<CardColor,CardNumber>& card2)
{
    return (card1.value() > card2.value());
}
template <class T, class U>
ostream& operator<<(ostream& os, const Card<T,U>& card)
{
    T card_num = card.getNumber();
    U card_color = card.getColor();
    os << int(card_num) << " ";
    switch (card_color) {
    case U::Red:
        os << "Merah";
        break;
    case U::Green:
        os << "Hijau";
        break;
    case U::Blue:
        os << "Biru";
        break;
    case U::Yellow:
        os << "Kuning";
        break;
    }
    return os;
}

ostream& operator<<(ostream& os, const Card<CardColor,CardNumber>& card)
{
    CardNumber card_num = card.getNumber();
    CardColor card_color = card.getColor();
    os << int(card_num) << " ";
    switch (card_color) {
    case CardColor::Red:
        os << "Merah";
        break;
    case CardColor::Green:
        os << "Hijau";
        break;
    case CardColor::Blue:
        os << "Biru";
        break;
    case CardColor::Yellow:
        os << "Kuning";
        break;
    }
    return os;
}
template class Card<CardColor,CardNumber>;
template class Card<CardSymbol,CangkulNumber>;