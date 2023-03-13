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

vector<Combo*>& Combo::getCombos()
{
    return combos;
}

// Implementation of Class HighCard
HighCard::HighCard() : Combo("HighCard") {}

HighCard::HighCard(const HighCard& other) : Combo(other) {}

bool HighCard::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    if (player.size() > 0) {
        return true;
    }
    return false;
}

Combo* HighCard::clone()
{
    HighCard* clone = this;
    return clone;
}

float HighCard::value() const
{
    return cards[0].value();
}

//Implementation of Class Pair
Pair::Pair() : Combo("Pair") {}
Pair::Pair(const Pair& other) : Combo(other) {}

bool compareCards(const Card& a,const Card& b){
    return a.value() > b.value();
}

bool Pair::isThereCombo(vector<Card>& player, vector<Card>& table) {
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

Combo* Pair::clone()
{
    return new Pair(*this);
}


float Pair::value() const
{
    // val maks = 2.78
    return cards[0].value() + 1.39;
} 

TwoPair::TwoPair() : Combo("TwoPair") {}
TwoPair::TwoPair(const TwoPair& other) : Combo(other) {}

bool TwoPair::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    return false;
}

Combo* TwoPair::clone()
{
    return new TwoPair(*this);
}

float TwoPair::value() const
{
    // val maks = 1315.7832
    float val = 2.78;
    val += int(cards[0].getNumber()) * 100 + int(cards[0].getColor()) * 0.001;
    val += int(cards[2].getNumber()) + int(cards[2].getColor()) * 0.0001;
    return val;
}

ThreeOfAKind::ThreeOfAKind() : Combo("ThreeOfAKind") {}
ThreeOfAKind::ThreeOfAKind(const ThreeOfAKind& other) : Combo(other) {}

bool ThreeOfAKind::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    return false;
}
Combo* ThreeOfAKind::clone()
{
    ThreeOfAKind* clone = this;
    return this;
}

float ThreeOfAKind::value() const
{
    // val maks = 2615.7832
    return int(cards[0].getNumber()) * 100 + 1315.7832;
}

Straight::Straight() : Combo("Straight") {}
Straight::Straight(const Straight& other) : Combo(other) {}

bool Straight::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    return false;
}
Combo* Straight::clone()
{
    return new Straight(*this);
}

float Straight::value() const
{
    // val maks = 3915.7832
    return int(cards[0].getNumber()) * 100 + 2615.7832;
}

Flush::Flush() : Combo("Flush") {}
Flush::Flush(const Flush& other) : Combo(other) {}

bool Flush::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    return false;
}

Combo* Flush::clone()
{
    Flush* clone = this;
    return this;
}

FullHouse::FullHouse() : Combo("FullHouse") {}
FullHouse::FullHouse(const FullHouse& other) : Combo(other) {}

bool FullHouse::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    return false;
}
Combo* FullHouse::clone()
{
    return new FullHouse(*this);
}

FourOfAKind::FourOfAKind() : Combo("FourOfAKind") {}
FourOfAKind::FourOfAKind(const FourOfAKind& other) : Combo(other) {}

bool FourOfAKind::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    return false;
}

Combo* FourOfAKind::clone()
{
    return new FourOfAKind(*this);
}

StraightFlush::StraightFlush() : Combo("StraightFlush") {}
StraightFlush::StraightFlush(const StraightFlush& other) : Combo(other) {}

bool StraightFlush::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    return false;
}

Combo* StraightFlush::clone()
{
    StraightFlush* clone = this;
    return new StraightFlush(*this);
}
