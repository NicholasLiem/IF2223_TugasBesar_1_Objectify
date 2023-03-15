#include "Card.hpp"
#include "Utils.hpp"

#include <iostream>
#include <string>
using namespace std;

template <class T, class U>
Card<T, U>::Card(const T color, const U number)
{
    this->color = color;
    this->number = number;
}

template <class T, class U>
Card<T, U>::Card(const int color, const int number)
{
    this->color = static_cast<T>(color);
    this->number = static_cast<U>(number);
}

template <class T, class U>
Card<T, U>::Card(const Card<T, U>& other)
{
    this->color = other.color;
    this->number = other.number;
}

template <class T, class U>
float Card<T, U>::value() const
{
    return int(number) + int(color) * 0.03;
}

template <class T, class U>
T Card<T, U>::getColor() const
{
    return color;
}

template <class T, class U>
U Card<T, U>::getNumber() const
{
    return number;
}

template <class T, class U>
bool Card<T, U>::operator==(const Card& card1)
{
    return (this->getNumber() == card1.getNumber());
}

template <class T, class U>
bool operator==(const Card<T, U>& card1, const Card<T, U>& card2)
{
    return (card1.getNumber() == card2.getNumber());
}

template <class T, class U>
Card<T, U>& Card<T, U>::operator=(const Card<T, U>& other)
{
    this->color = other.color;
    this->number = other.number;
    return *this;
}

template <class T, class U>
bool operator<(const Card<T, U>& card1, const Card<T, U>& card2)
{
    return (card1.value() < card2.value());
}

template <class T, class U>
bool operator>(const Card<T, U>& card1, const Card<T, U>& card2)
{
    return (card1.value() > card2.value());
}

std::ostream& operator<<(std::ostream& out, const CardColor& color)
{
    switch (color) {
    case CardColor::Red:
        out << "Merah";
        break;
    case CardColor::Yellow:
        out << "Kuning";
        break;
    case CardColor::Green:
        out << "Hijau";
        break;
    case CardColor::Blue:
        out << "Biru";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const CardNumber& number)
{
    out << int(number);
    return out;
}

std::ostream& operator<<(std::ostream& out, const CardSymbol& symbol)
{
    switch (symbol) {
    case CardSymbol::Diamond:
        out << "Diamond";
        break;
    case CardSymbol::Club:
        out << "Club";
        break;
    case CardSymbol::Heart:
        out << "Heart";
        break;
    case CardSymbol::Spade:
        out << "Spade";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const CangkulNumber& number)
{
    out << int(number);
    return out;
}

template class Card<CardColor, CardNumber>;
template class Card<CardSymbol, CangkulNumber>;
