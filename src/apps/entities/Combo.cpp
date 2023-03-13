#include "../../lib/entities/Combo.hpp"

// Implementation of Class Combo
vector<Combo*> Combo::combos;

Combo::Combo(string name) : name(name) {}

Combo::Combo(const Combo& other) : name(other.name), cards(other.cards) {}

void Combo::registerCombo(Combo* combo)
{
    combos.push_back(combo);
}

void Combo::clearCombos()
{
    combos.clear();
}


string Combo::getName(){
    return this->name;
}

vector<Combo*>& Combo::getCombos(){
    return combos;
}

// Implementation of Class HighCard
HighCard::HighCard() : Combo("HighCard") {}

HighCard::HighCard(const HighCard& other) : Combo(other) {}

bool HighCard::isThereCombo(vector<Card>& cards)
{
    if (cards.size() > 0) {
        return true;
    }
    return false;
}

float HighCard::value() const{
    return 0.0;
}

Combo* HighCard::clone()
{
    HighCard* clone = this;
    return clone;
}

//Implementation of Class Pair
Pair::Pair() : Combo("Pair") {}
Pair::Pair(const Pair& other) : Combo(other) {}
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

Combo* Pair::clone()
{
    return new Pair(*this);
}

float Pair::value() const
{
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
TwoPair::TwoPair(const TwoPair& other) : Combo(other) {}

bool TwoPair::isThereCombo(vector<Card>& cards)
{
    int pair = 0;
    for(int i = 0; i < cards.size();i++){
        int count = 1;
        for(int j = i + 1; j < cards.size();j++){
            if(cards[i] == cards[j]){
                count++;
            }
        }
        if(count == 2){
            pair++;
        }
    }
    if(pair == 2){
        return true;
    }else{
        return false;
    }
}

float TwoPair::value()const{
    return 0.0;
}

Combo* TwoPair::clone()
{
    return new TwoPair(*this);
}

ThreeOfAKind::ThreeOfAKind() : Combo("ThreeOfAKind") {}
ThreeOfAKind::ThreeOfAKind(const ThreeOfAKind& other) : Combo(other) {}

float ThreeOfAKind::value()const{
    return 0.0;
}

Combo* ThreeOfAKind::clone()
{
    ThreeOfAKind* clone = this;
    return this;
}

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

Straight::Straight() : Combo("Straight") {}
Straight::Straight(const Straight& other) : Combo(other) {}

bool Straight::isThereCombo(vector<Card>& cards)
{
    return false;
}

float Straight::value()const{
    return 0.0;
}

Combo* Straight::clone()
{
    return new Straight(*this);
}

Flush::Flush() : Combo("Flush") {}
Flush::Flush(const Flush& other) : Combo(other) {}

bool Flush::isThereCombo(vector<Card>& cards)
{
    return false;
}

float Flush::value()const{
    return 0.0;
}

Combo* Flush::clone()
{
    Flush* clone = this;
    return this;
}

FullHouse::FullHouse() : Combo("FullHouse") {}
FullHouse::FullHouse(const FullHouse& other) : Combo(other) {}

bool FullHouse::isThereCombo(vector<Card>& cards)
{
    return false;
}

float FullHouse::value()const{
    return 0.0;
}

Combo* FullHouse::clone()
{
    return new FullHouse(*this);
}

FourOfAKind::FourOfAKind() : Combo("FourOfAKind") {}
FourOfAKind::FourOfAKind(const FourOfAKind& other) : Combo(other) {}

bool FourOfAKind::isThereCombo(vector<Card>& cards)
{
    return false;
}

float FourOfAKind::value()const{
    return 0.0;
}

Combo* FourOfAKind::clone()
{
    return new FourOfAKind(*this);
}



StraightFlush::StraightFlush() : Combo("StraightFlush") {}
StraightFlush::StraightFlush(const StraightFlush& other) : Combo(other) {}

bool StraightFlush::isThereCombo(vector<Card>& cards)
{
    return false;
}

float StraightFlush::value() const{
    return 0.0;   
}


Combo* StraightFlush::clone()
{
    StraightFlush* clone = this;
    return new StraightFlush(*this);
}
