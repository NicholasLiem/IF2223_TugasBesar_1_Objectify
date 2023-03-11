#include "./lib/entities/Card.hpp"
#include <iostream>
using namespace std;

Card::Card(const CardColor color, const CardNumber number){
    this->color = color;
    this->number = number;
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



// int main(){
//     Card *c1 = new Card(CardColor GREEN, CardNumber ONE);
//     cout << "Hello World" << endl;
//     return 0;
// }








