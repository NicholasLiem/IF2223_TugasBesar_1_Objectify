#include "../../lib/entities/Combo.hpp"

// Implementation of Class Combo
vector<Combo*> Combo::combos;

Combo::Combo(string name) : name(name) {}

Combo::Combo(Combo& other) : name(other.name), cards(other.cards) {}

void Combo::registerCombo(Combo* combo){
    combos.push_back(combo);
}

void Combo::clearCombos(){
    combos.clear();
}

vector<Combo*>& Combo::getCombos(){
    return combos;
}

// Implementation of Class HighCard
HighCard::HighCard(): Combo("HighCard"){}

bool HighCard::isThereCombo(vector<Card>& cards){
    if (cards.size() > 0){
        return true;
    }
    return false;
}

Combo* HighCard::clone() {
    HighCard *clone = this;
    return clone;
}

float HighCard::value() {
    return cards[0].value();
}


//Implementation of Class Pair
Pair::Pair() : Combo("Pair") {}
bool Pair::isThereCombo(vector<Card>& cards) {
    for(int i = 0; i < cards.size();i++){
        for(int j = i; j < cards.size();j++){
            if(cards[i] == cards[j]){
                return true;
            }
        }
    }
    return false;
}
Pair* Pair::clone() {
    Pair *clone = this;
    return clone;


}
float Pair::value() {
    float val = 1.39;
    float val1 = cards[0].value();
    float val2 = cards[1].value();
    if(val1 > val2){
        val += val1;
    } else {
        val += val2;
    }
    return val;
}

TwoPair::TwoPair() : Combo("TwoPair") {}
bool TwoPair::isThereCombo(vector<Card>& cards) {
    return false;
}
TwoPair* TwoPair::clone() {
    TwoPair *clone = this;
    return this;
}

ThreeOfAKind::ThreeOfAKind() : Combo("ThreeOfAKind"){}
bool ThreeOfAKind::isThereCombo(vector<Card>& cards) {
    return false;
}
ThreeOfAKind* ThreeOfAKind::clone() {
    ThreeOfAKind *clone = this;
    return this;
}

Straight::Straight() : Combo("Straight"){}
bool Straight::isThereCombo(vector<Card>& cards) {
    return false;
}
Straight* Straight::clone() {
    Straight *clone = this;
    return this;
}

Flush::Flush() : Combo("Flush") {}
bool Flush::isThereCombo(vector<Card>& cards) {
    return false;
}
Flush* Flush::clone() {
    Flush *clone = this;
    return this;
}

FullHouse::FullHouse() : Combo("FullHouse"){}
bool FullHouse::isThereCombo(vector<Card>& cards) {
    return false;
}
FullHouse* FullHouse::clone() {
    FullHouse *clone = this;
    return this;
}

FourOfAKind::FourOfAKind() : Combo("FourOfAKind") {}
bool FourOfAKind::isThereCombo(vector<Card>& cards) {
    return false;
}
FourOfAKind* FourOfAKind::clone() {
    FourOfAKind *clone = this;
    return this;
}

StraightFlush::StraightFlush() : Combo("StraightFlush") {}
bool StraightFlush::isThereCombo(vector<Card>& cards) {
    return false;
}
StraightFlush* StraightFlush::clone() {
    StraightFlush *clone = this;
    return this;
}