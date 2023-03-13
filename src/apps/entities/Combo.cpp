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
    return new HighCard(*this);
}

float HighCard::value() {
    return cards[0].value();
}


//Implementation of Class Pair
Pair::Pair() : Combo("Pair") {}
bool Pair::isThereCombo(vector<Card>& cards) {}
Pair* Pair::clone() {

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
bool TwoPair::isThereCombo(vector<Card>& cards) {}
TwoPair* TwoPair::clone() {}

ThreeOfAKind::ThreeOfAKind() : Combo("ThreeOfAKind"){}
bool ThreeOfAKind::isThereCombo(vector<Card>& cards) {}
ThreeOfAKind* ThreeOfAKind::clone() {}

Straight::Straight() : Combo("Straight"){}
bool Straight::isThereCombo(vector<Card>& cards) {}
Straight* Straight::clone() {}

Flush::Flush() : Combo("Flush") {}
bool Flush::isThereCombo(vector<Card>& cards) {}
Flush* Flush::clone() {}

FullHouse::FullHouse() : Combo("FullHouse"){}
bool FullHouse::isThereCombo(vector<Card>& cards) {}
FullHouse* FullHouse::clone() {}

FourOfAKind::FourOfAKind() : Combo("FourOfAKind") {}
bool FourOfAKind::isThereCombo(vector<Card>& cards) {}
FourOfAKind* FourOfAKind::clone() {}

StraightFlush::StraightFlush() : Combo("StraightFlush") {}
bool StraightFlush::isThereCombo(vector<Card>& cards) {}
StraightFlush* StraightFlush::clone() {}