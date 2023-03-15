#include "Card.hpp"

#include "Utils.hpp"

#include <iostream>
#include <string>
using namespace std;

Card::Card(const CardColor color, const CardNumber number)
{
    this->color = color;
    this->number = number;
}

Card::Card(const int color, const int number)
{
    this->color = static_cast<CardColor>(color);
    this->number = static_cast<CardNumber>(number);
}

Card::Card(const Card& other)
{
    this->color = other.color;
    this->number = other.number;
}

float Card::value() const
{
    return int(number) + int(color) * 0.03;
}

CardColor Card::getColor() const
{
    return color;
}

CardNumber Card::getNumber() const
{
    return number;
}

bool Card::operator==(const Card& card1)
{
    return (this->getNumber() == card1.getNumber());
}

bool operator==(const Card& card1, const Card& card2)
{
    return (card1.getNumber() == card2.getNumber());
}

Card& Card::operator=(const Card& other)
{
    this->color = other.color;
    this->number = other.number;
    return *this;
}

bool operator<(const Card& card1, const Card& card2)
{
    return (card1.value() < card2.value());
}

bool operator>(const Card& card1, const Card& card2)
{
    return (card1.value() > card2.value());
}

ostream& operator<<(ostream& out, const CardColor& color)
{
    switch (color) {
    case CardColor::Red:
        out << "Merah";
        break;
    case CardColor::Green:
        out << "Hijau";
        break;
    case CardColor::Blue:
        out << "Biru";
        break;
    case CardColor::Yellow:
        out << "Kuning";
        break;
    }
    return out;
}

ostream& operator<<(ostream& out, const CardNumber& number)
{
    out << int(number);
    return out;
}

ostream& operator<<(ostream& os, const Card& card)
{
    os << card.getNumber() << " " << card.getColor();
    return os;
}

istream& operator>>(istream& in, CardColor& color)
{
    string line;
    in >> line;
    string str_color = Utils::to_lower(line);
    if (str_color == "merah") {
        color = CardColor::Red;
    } else if (str_color == "kuning") {
        color = CardColor::Yellow;
    } else if (str_color == "biru") {
        color = CardColor::Blue;
    } else if (str_color == "hijau") {
        color = CardColor::Green;
    } else {
        throw "Invalid card color: " + line;
    }
    return in;
}

istream& operator>>(istream& in, CardNumber& number)
{
    int num;
    in >> num;
    if (num < 1 || num > 13) {
        throw "Invalid card number: " + to_string(num);
    } else {
        number = static_cast<CardNumber>(num);
    }
    return in;
}

istream& operator>>(istream& in, Card& card)
{
    CardNumber number;
    CardColor color;
    try {
        in >> number >> color;
        card.number = number;
        card.color = color;
    } catch (const string& e) {
        throw "Error parsing string: " + string(e);
    }
    return in;
}
