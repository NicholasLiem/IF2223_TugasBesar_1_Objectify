#include "../../lib/entities/Combo.hpp"

vector<Combo*> Combo::combos;

Combo::Combo(string name) : name(name) {}

Combo::Combo(Combo& other) : name(other.name) {
    cards = other.cards;
}

void Combo::registerCombo(Combo* combo){
    cout << "Register combo" << endl;
    Combo::combos.push_back(combo);
    cout << combo->getName();
}

void Combo::clearCombos(){
    combos.clear();
}


string Combo::getName(){
    return this->name;
}

vector<Combo*>& Combo::getCombos(){
    return combos;
}

HighCard::HighCard(Card c): Combo("HighCard"){}

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

Pair::Pair(vector<Card> _cards) : Combo("Pair") {}
bool Pair::isThereCombo(vector<Card>& cards) {
    for(int i = 0; i < cards.size();i++){
        int count = 1;
        for(int j = i; j < cards.size();j++){
            if(cards[i] == cards[j]){
                count++;
            }
        }
        if(count == 2){
            return true;
        }
    }
    return false;
}
Combo* Pair::clone() {
    Pair *clone = this;
    return clone;
}

TwoPair::TwoPair(vector<Card> _cards) : Combo("TwoPair") {}
bool TwoPair::isThereCombo(vector<Card>& cards) {
    return false;
}
Combo* TwoPair::clone() {
    TwoPair *clone = this;
    return this;
}

ThreeOfAKind::ThreeOfAKind(vector<Card> _cards) : Combo("ThreeOfAKind"){}
bool ThreeOfAKind::isThereCombo(vector<Card>& cards) {
    for(int i = 0 ; i < cards.size();i++){
        int count = 1;
        for(int j = i+1; j < cards.size();j++){
            if(cards[i] == cards[j]){
                count++;
            }
        }
        if(count == 3){
            return true;
        }
    }
    return false;
}
Combo* ThreeOfAKind::clone() {
    ThreeOfAKind *clone = this;
    return this;
}

Straight::Straight(vector<Card> _cards) : Combo("Straight"){}
bool Straight::isThereCombo(vector<Card>& cards) {
    return false;
}
Combo* Straight::clone() {
    Straight *clone = this;
    return this;
}

Flush::Flush(vector<Card> _cards) : Combo("Flush") {}
bool Flush::isThereCombo(vector<Card>& cards) {
    return false;
}
Combo* Flush::clone() {
    Flush *clone = this;
    return this;
}

FullHouse::FullHouse(vector<Card> _cards) : Combo("FullHouse"){}
bool FullHouse::isThereCombo(vector<Card>& cards) {
    return false;
}
Combo* FullHouse::clone() {
    FullHouse *clone = this;
    return this;
}

FourOfAKind::FourOfAKind(vector<Card> _cards) : Combo("FourOfAKind") {}
bool FourOfAKind::isThereCombo(vector<Card>& cards) {
    return false;
}
Combo* FourOfAKind::clone() {
    FourOfAKind *clone = this;
    return this;
}

StraightFlush::StraightFlush(vector<Card> _cards) : Combo("StraightFlush") {}
bool StraightFlush::isThereCombo(vector<Card>& cards) {
    return false;
}
Combo* StraightFlush::clone() {
    StraightFlush *clone = this;
    return this;
}