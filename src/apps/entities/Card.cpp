#include "../../lib/entities/Card.hpp"

#include <iostream>
using namespace std;



Card::Card(const CardColor color, const CardNumber number)
{
    this->color = color;
    this->number = number;
}

Card::Card(const int color, const int number)
{
    this->color = static_cast<CardColor>(color-1);
    this->number = static_cast<CardNumber>(number-1);
}

Card::Card(const Card& other)
{
    this->color = other.color;
    this->number = other.number;
}

float Card::value() const
{
    return int(number) + int(color) * 0.003;
}

CardColor Card::getColor() const
{
    return color;
}

CardNumber Card::getNumber() const
{
    return number;
}
int Card::getNumberInt()const{
    return (int)number;
}

int Card::getColorString()const{
    return (int)color;
}

bool Card::operator==(const Card& card1){
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
    return (card1.getNumber() < card2.getNumber());
}

bool operator>(const Card& card1, const Card& card2)
{
    return (card1.getNumber() > card2.getNumber());
}

ostream& operator<<(ostream& os, const Card& card)
{
    CardNumber card_num = card.getNumber();
    CardColor card_color = card.getColor();
    os << "Card: ";
    switch (card_color) {
    case CardColor::Red:
        std::cout << "RED";
        break;
    case CardColor::Green:
        std::cout << "GREEN";
        break;
    case CardColor::Blue:
        std::cout << "BLUE";
        break;
    case CardColor::Yellow:
        std::cout << "YELLOW";
        break;
    }
    os << " " << int(card_num) << endl;
    return os;
}

// int main(){
//     Card c1(0,1);
   
//     Card c2(1,1);
//     if(c1 == c2){
//         cout << "Pair" << endl;
//     }else{
//         cout << "Not a pair!" << endl;
//     }
//     return 0;
// }