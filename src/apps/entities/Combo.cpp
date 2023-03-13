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
        sort(player.begin(),player.end(),compareCards);
        this->cards.push_back(player[0]);
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
    // max value = 1.39
    return cards[0].value();
}

//Implementation of Class Pair
Pair::Pair() : Combo("Pair") {}
Pair::Pair(const Pair& other) : Combo(other) {}

bool compareCards(const Card& a,const Card& b){
    return a.value() > b.value();
}

bool Pair::isThereCombo(vector<Card>& player, vector<Card>& table) {
    sort(player.begin(),player.end(),compareCards);
    for(int i = 0; i < player.size(); i++){
        for(int j = 0; j < table.size(); j++){
            if(player[i] == table[j]){
                this->cards.push_back(player[i]);
                this->cards.push_back(table[j]);
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
    // max value = 13131.3996
    float val = 1.39 + int(cards[0].getNumber()) * 10 + int(cards[0].getColor()) * 0.003 + int(cards[1].getNumber()) * 1000 + int(cards[1].getColor()) * 0.0003;
    return val;
}

TwoPair::TwoPair() : Combo("TwoPair") {}
TwoPair::TwoPair(const TwoPair& other) : Combo(other) {}

bool TwoPair::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    if (table.size() > 1) {
        for (int i = 0; i < table.size(); i++){
            if (player[0] == table[i]){
                for (int j = 0; j < table.size(); j++){
                    if (player[1] == table[j]){
                        cards.push_back(player[0]);
                        cards.push_back(table[i]);
                        cards.push_back(player[1]);
                        cards.push_back(player[j]);
                        sort(cards.begin(),cards.end(),compareCards);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

Combo* TwoPair::clone()
{
    return new TwoPair(*this);
}

float TwoPair::value() const
{
    // max value = 26261.39969696
    float val = 13131.3996;
    val += int(cards[0].getNumber()) * 10 + int(cards[0].getColor()) * 0.00003 + int(cards[1].getColor()) * 0.000003;
    val += int(cards[2].getNumber()) * 1000 + int(cards[2].getColor()) * 0.0000003 + int(cards[3].getColor()) * 0.00000003;
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

float Flush::value() const {
    return 0;
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

float FullHouse::value() const {
    return 0;
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

float FourOfAKind::value() const {
    return 0;
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

float StraightFlush::value() const {
    return 0;
}

Combo* StraightFlush::clone()
{
    StraightFlush* clone = this;
    return new StraightFlush(*this);
}
