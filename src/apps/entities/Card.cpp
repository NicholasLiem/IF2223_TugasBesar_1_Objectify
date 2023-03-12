#include "../../lib/entities/Card.hpp"
#include <iostream>
using namespace std;

Card::Card(const CardColor color, const CardNumber number){
    this->color = color;
    this->number = number;
}

Card::Card(const int color, const int number){
    switch (color)
    {
    case 1:this->color = CardColor::Green;break;
    case 2 : this->color = CardColor::Blue;break;
    case 3 : this->color = CardColor::Yellow;break;
    case 4 : this->color = CardColor::Red;break;
    default:
        break;
    }

    switch (number)
    {
    case 1:this->number = CardNumber::One;break;
    case 2:this->number = CardNumber::Two;break;
    case 3 : this->number = CardNumber::Three;break;
    case 4 : this->number = CardNumber::Four;break;
    case 5 : this->number = CardNumber::Five;break;
    case 6 : this->number = CardNumber::Six;break;
    case 7 : this->number = CardNumber::Seven;break;
    case 8 : this->number = CardNumber::Eight;break;
    case 9 : this->number = CardNumber::Nine;break;
    case 10 : this->number = CardNumber::Ten;break;
    case 11 : this->number = CardNumber::Eleven;break;
    case 12 : this->number = CardNumber::Twelve;break;
    case 13 : this->number = CardNumber::Thirteen;break;
    default:break;
    }
}

Card::Card(const Card& other){
    this->color = other.color;
    this->number = other.number;
}

float Card::value() const{
    return int(number) + int(color) * 0.003;
}

CardColor Card::getColor() const{
    return color;
}

CardNumber Card::getNumber() const{
    return number;
}

bool operator==(const Card& card1, const Card& card2){
    return card1.value() == card2.value();
}

Card& Card::operator=(const Card& other){
    this->color = other.color;
    this->number = other.number;
    return *this;
}

bool operator<(const Card& card1, const Card& card2){
    return (card1.value() < card2.value());
}

bool operator>(const Card& card1, const Card& card2){
    return (card1.value() > card2.value());
}

ostream& operator<<(ostream& os, const Card& card){
        CardNumber card_num = card.getNumber();
        CardColor card_color = card.getColor();
        os << "Card: ";
        switch(card_color)
          {
              case CardColor::Red  : std::cout << "RED";   break;
              case CardColor::Green : std::cout << "GREEN"; break;
              case CardColor::Blue : std::cout << "BLUE";  break;
              case CardColor::Yellow : std::cout << "YELLOW";  break;
          }
        os << " " << int(card_num) << endl;
        return os;
    }








