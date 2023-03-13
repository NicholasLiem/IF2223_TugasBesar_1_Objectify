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

bool compareCards(const Card& a,const Card& b){
    return a > b;
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


bool Pair::isThereCombo(vector<Card>& player, vector<Card>& table) {
    sort(player.begin(),player.end(),compareCards);
    if (player[0] == player[1]){
        cards.push_back(player[0]);
        cards.push_back(player[1]);
        return true;
    } else {
        for(int i = 0; i < player.size(); i++){
            for(int j = 0; j < table.size(); j++){
                if(player[i] == table[j]){
                    cards.push_back(player[i]);
                    cards.push_back(table[j]);
                    sort(cards.begin(),cards.end(),compareCards);
                    return true;
                }
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
    float val = 1.39 + int(cards[0].getNumber()) * 1000 + int(cards[0].getColor()) * 0.003 + int(cards[1].getNumber()) * 10 + int(cards[1].getColor()) * 0.0003;
    return val;
}

TwoPair::TwoPair() : Combo("TwoPair") {}
TwoPair::TwoPair(const TwoPair& other) : Combo(other) {}

bool TwoPair::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    if (table.size() > 1) {
        if (player[0] == player[1]){
            for (int i = 0; i < table.size(); i++){
                for (int j = 0; j < table.size(); j++){
                    if (table[i] == table[j]){
                        cards.push_back(player[0]);
                        cards.push_back(player[1]);
                        cards.push_back(table[i]);
                        cards.push_back(table[j]);
                        sort(cards.begin(),cards.end(),compareCards);
                        return true;
                    }
                }
            }
        } else {
            for (int i = 0; i < table.size(); i++){
                if (player[0] == table[i]){
                    for (int j = 0; j < table.size(); j++){
                        if (player[1] == table[j]){
                            cards.push_back(player[0]);
                            cards.push_back(table[i]);
                            cards.push_back(player[1]);
                            cards.push_back(table[j]);
                            sort(cards.begin(),cards.end(),compareCards);
                            return true;
                        }
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
    val += int(cards[0].getNumber()) * 1000 + int(cards[0].getColor()) * 0.00003 + int(cards[1].getColor()) * 0.000003;
    val += int(cards[2].getNumber()) * 10 + int(cards[2].getColor()) * 0.0000003 + int(cards[3].getColor()) * 0.00000003;
    return val;
}

ThreeOfAKind::ThreeOfAKind() : Combo("ThreeOfAKind") {}
ThreeOfAKind::ThreeOfAKind(const ThreeOfAKind& other) : Combo(other) {}

bool ThreeOfAKind::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    if (player[0] == player[1]){
        for (int i = 0; i < table.size(); i++){
            if (table[i] == player[0]){
                cards.push_back(player[0]);
                cards.push_back(player[1]);
                cards.push_back(table[i]);
                sort(cards.begin(),cards.end(),compareCards);
                return true;
            }
        }
    } else {
        for (int h = 0; h < player.size(); h++){
            for (int i = 0; i < table.size(); i++){
                if (player[h] == table[i]){
                    for (int j = i + 1; j < table.size(); j++){
                        if (player[h] == table[j]){
                            cards.push_back(player[h]);
                            cards.push_back(table[i]);
                            cards.push_back(table[j]);
                            sort(cards.begin(),cards.end(),compareCards);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

Combo* ThreeOfAKind::clone()
{
    ThreeOfAKind* clone = this;
    return this;
}

float ThreeOfAKind::value() const
{
    // val maks = 1326261.39969696963
    return 26261.39969696 + int(cards[0].getNumber()) * 100000 + int(cards[0].getColor()) * 0.000000003 + int(cards[1].getColor()) * 0.0000000003 + int(cards[2].getColor()) * 0.00000000003;
}

Straight::Straight() : Combo("Straight") {}
Straight::Straight(const Straight& other) : Combo(other) {}

bool Straight::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    if (table.size() > 2){
        vector<Card> temp;
        for (int i = 0; i < player.size(); i++){
            temp.push_back(player[i]);
        }
        for (int i = 0; i < table.size(); i++){
            temp.push_back(table[i]);
        }
        sort(temp.begin(),temp.end(),compareCards);
        int num = int(temp[0].getNumber()) - 1;
        bool straight = true;
        for (int i = 1; i < temp.size(); i++){
            if(int(temp[i].getNumber()) != num){
                straight = false;
            }
            num--;
        }
        if (straight){
            return true;
        }
    }
    return false;
}

Combo* Straight::clone()
{
    return new Straight(*this);
}

float Straight::value() const
{
    // val maks = 2626261.3996969696399996
    float val = 1326261.39969696963 + int(cards[0].getNumber()) * 100000;
    float constant = 0.000000000003 ;
    for (int i = 0; i < 5; i++){
        val += int(cards[i].getColor())*constant;
        constant /= 10;
    }
    return val;
}

Flush::Flush() : Combo("Flush") {}
Flush::Flush(const Flush& other) : Combo(other) {}

bool Flush::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    
    return false;
}

float Flush::value() const {
    // max value = 13133939391.39969696963999969
    float val = 2626261.3996969696399996 + int(cards[0].getColor())*0.00000000000000003;
    int constant = 10;
    for (int i = 4; i >= 0; i--){
        val += int(cards[i].getNumber())*constant;
        constant *= 100;
    }
    return val;
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
    // max value = 26263939391.3996969696399996996396
    float val = 13133939391.39969696963999969 + int(cards[0].getNumber())*1000000000 + int(cards[3].getNumber())*10000000;
    float constant = 0.000000000000000003;
    for (int i = 0; i < 5; i++){
        val += int(cards[i].getColor())*constant;
        constant /= 10;
    }
    return val;
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
    // max value = 26393939391.3996969696399996996396
    float val = 26263939391.3996969696399996996396 + int(cards[0].getNumber())*1000000;
    return val;
}

Combo* FourOfAKind::clone()
{
    return new FourOfAKind(*this);
}



StraightFlush::StraightFlush() : Combo("StraightFlush") {}
StraightFlush::StraightFlush(const StraightFlush& other) : Combo(other) {}

bool StraightFlush::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    vector<Card> temp;
    return false;
}

float StraightFlush::value() const {
    // max value = 39393939391.39969696963999969963969
    float val = 26393939391.3996969696399996996396 + int(cards[0].getNumber())*100000000 + int(cards[0].getColor())*0.00000000000000000000003;
    return val;
}

Combo* StraightFlush::clone()
{
    StraightFlush* clone = this;
    return new StraightFlush(*this);
}
