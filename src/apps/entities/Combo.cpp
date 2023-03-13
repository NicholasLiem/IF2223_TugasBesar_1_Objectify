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

bool compareCards(const Card& a,const Card& b){
    return a.value() > b.value();
}

bool Pair::isThereCombo(vector<Card>& cards) {
    for(int i = 0; i < cards.size();i++){
        for(int j = i; j < cards.size();j++){
            if(cards[i] == cards[j]){
                this->cards.push_back(cards[i]);
                this->cards.push_back(cards[j]);
                sort(this->cards.begin(),this->cards.end(),compareCards);
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
    // val maks = 2.78
    return cards[0].value() + 1.39;
}

TwoPair::TwoPair() : Combo("TwoPair") {}
bool TwoPair::isThereCombo(vector<Card>& cards) {
    return false;
}
TwoPair* TwoPair::clone() {
    TwoPair *clone = this;
    return this;
}

float TwoPair::value(){
    // val maks = 1315.7832
    float val = 2.78;
    val += int(cards[0].getNumber()) * 100 + int(cards[0].getColor()) * 0.001;
    val += int(cards[2].getNumber()) + int(cards[2].getColor()) * 0.0001;
    return val;
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