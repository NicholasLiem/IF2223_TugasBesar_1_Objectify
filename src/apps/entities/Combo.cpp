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

// Implementation of additional functions
bool compareCards(const Card& a,const Card& b){
    return a > b;
}

bool isMember(vector<Card>& cards, Card card){
    auto itr = find(cards.begin(),cards.end(),card);
    if (itr != cards.end()){
        return true;
    }
}

bool foundPlayerCard(vector<Card>& temp, vector<Card>& player){
    for (int j = 0; j < 2; j++){
        isMember(temp,player[j]);
    }
    return false;
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
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 5; j++){
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
    if (player[0] == player[1]){
        for (int i = 0; i < 5; i++){
            for (int j = i + 1; j < 5; j++){
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
        for (int i = 0; i < 5; i++){
            if (player[0] == table[i]){
                for (int j = 0; j < 5; j++){
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
        for (int i = 0; i < 5; i++){
            if (table[i] == player[0]){
                cards.push_back(player[0]);
                cards.push_back(player[1]);
                cards.push_back(table[i]);
                sort(cards.begin(),cards.end(),compareCards);
                return true;
            }
        }
    } else {
        for (int h = 0; h < 2; h++){
            for (int i = 0; i < 5; i++){
                if (player[h] == table[i]){
                    for (int j = i + 1; j < 5; j++){
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

bool Straight::isThereCombo(vector<Card>& player, vector<Card>& table) {
    vector<Card> allCards = player;
    allCards.insert(allCards.end(), table.begin(), table.end());
    sort(allCards.begin(), allCards.end(), compareCards);

    for (int i = 0; i < 7; i++){
        cout << int(allCards[i].getNumber()) << endl;
    }

    int straightCount = 1;
    int currentRank = int(allCards[0].getNumber());

    vector<Card> temp;
    temp.push_back(allCards[0]);
    for (int i = 1; i < 7; i++) {
        if (int(allCards[i].getNumber()) == currentRank - 1) {
            straightCount++;
            currentRank--;
            temp.push_back(allCards[i]);
            if (straightCount == 5){
                if (foundPlayerCard(temp,player)){
                    return true;
                } else {
                    temp.erase(temp.begin());
                    straightCount--;
                }
            }
        }
        else if (int(allCards[i].getNumber()) == currentRank) {
            if(!foundPlayerCard(temp,player) && isMember(player,allCards[i])){
                temp.erase(temp.begin() + straightCount - 1);
                temp.push_back(allCards[i]);                
            }
        }
        else {
            temp.clear();
            temp.push_back(allCards[i]);
            straightCount = 1;
            currentRank = int(allCards[i].getNumber());
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
    // Memastikan semua card dalam table tidak membentuk flush
    bool allTable = true;
    bool playerHas = false;
    for(int i = 0; i < 5-1;i++){
        if(table[i].getColor() != table[0].getColor()){
            allTable = false;
        }
    }
    sort(table.begin(),table.end(),compareCards);

    // Kalau semua card dalam table membentuk flush, return false
    if(allTable){
        for(int i = 0; i < 2;i++){
            if(player[i].getColor() == table[0].getColor()){
                playerHas = true;
                break;
            }
        }
        if(!playerHas){
            return false;
        }else{
            sort(player.begin(),player.end(),compareCards);
            // Kondisi : player ada kartu yang sama kayak di table
            int temp = 0;
            if(player[0].getColor() == table[4].getColor()){
                    cards.push_back(player[0]);
                    if(player[1].getColor() == player[0].getColor() && player[1].getNumber() > table[3].getNumber()){
                        cards.push_back(player[1]);
                        temp = 3;
                        for(int i = 0; i < 3;i++){
                            cards.push_back(table[i]);
                        }
                    }else{
                        temp = 4;
                    }
                    for(int i = 0; i < temp;i++){
                        cards.push_back(table[i]);
                    }
            }
            else{
                cards.push_back(player[1]);
                for(int i = 0; i < 4;i++){
                    cards.push_back(table[i]);
                }
            }
            sort(cards.begin(),cards.end(),compareCards);
            for(int i = 0; i < cards.size();i++){
                cout << cards[i] << endl;
            }
            return true;
        }
    }else{
        if(player[0].getColor() == player[1].getColor()){
            int count = 2;
            // Memasukkan kartu player ke dalam cards
            cards.push_back(player[0]);
            cards.push_back(player[1]);
            // Sort cards, sehingga kartu terbesar berada di cards[0]
            sort(cards.begin(),cards.end(),compareCards);
            int i = 0;
            while(count != 5 && i < 5){
                if(table[i].getColor() == cards[0].getColor()){
                    count++;
                    cards.push_back(table[i]);
                }
                i++;
            }
            if(count != 5){
                return false;
            }else{
                sort(cards.begin(),cards.end(),compareCards);
                while(i < 5){
                    if(table[i] > cards[4] && table[i].getColor() == cards[4].getColor()){
                        cards.pop_back();
                        cards.push_back(table[i]);
                        sort(cards.begin(),cards.end(),compareCards);
                    }
                    i++;
                }
                for(int i = 0; i < cards.size();i++){
                    cout << cards[i] << endl;
                }
                return true;
            }
            
        }
        // Kasus dimana player memiliki dua kartu yang warnanya berbeda - beda
        else{
            // cout << "Warna kartu player beda - beda"<< endl;
            int countOne = 1;
            int countTwo = 1;
            sort(cards.begin(),cards.end(),compareCards);
            // cout << "Done sorting" << endl;
            for(int i = 0; i < 5;i++){
                if(table[i].getColor() == player[0].getColor()){
                    countOne++;
                }
                if(table[i].getColor() == player[1].getColor()){
                    countTwo++;
                }
            }
            if(countOne < 5 && countTwo < 5){
                return false;
            }else if(countOne >= 5){
                cards.push_back(player[0]);
                for(int i = 0; i < 5;i++){
                    if(table[i].getColor() == player[0].getColor()){
                        cards.push_back(table[i]);
                    }
                }
                for(int i = 0; i < cards.size();i++){
                    cout << cards[i] << endl;
                }
                return true;
            }else{
                cards.push_back(player[1]);
                for(int i = 0; i < 5;i++){
                    if(table[i].getColor() == player[1].getColor()){
                        cards.push_back(table[i]);
                    }
                }
                for(int i = 0; i < cards.size();i++){
                    cout << cards[i] << endl;
                }
                return true;
            }
        }
    
    }

    
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
    vector<Card> allCards = player;
    allCards.insert(allCards.end(), table.begin(), table.end());
    sort(allCards.begin(), allCards.end(),compareCards);

    bool foundPair = false;
    bool foundTriplet = false;

    vector<Card> temp1;
    vector<Card> temp2;
    for (int i = 0; i < 5; i++) {
        if (allCards[i] == allCards[i+1] && allCards[i+1] == allCards[i+2]) {
            for (int j = i; j < i + 3; j++){
                temp1.push_back(allCards[j]);
            }
            foundTriplet = true;
            i += 2;
        }
        else if (allCards[i] == allCards[i+1]) {
            for (int j = i; j < i + 2; j++){
                temp2.push_back(allCards[j]);
            }
            foundPair = true;
            i += 1;
        }
        if (foundPair && foundTriplet) {
            vector<Card> temp = temp1;
            temp.insert(temp.end(),temp2.begin(),temp2.end());
            if (foundPlayerCard(temp,player)){
                cards.insert(cards.end(),temp.begin(),temp.end());
                return true;
            }
        }
    }
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
    if (player[0] == player[1]){
        int count = 0;
        for(int i = 0; i < 5; i++){
            if(table[i] == player[0]){
                count++;
            }
        }
        if (count == 2){
            int num = int(player[0].getNumber());
            for (int i = 0; i < 4; i++){
                cards.push_back(Card(i,num));
            }
            return true;
        }
    } else {
        for (int j = 0; j < 2; j++){
            int count = 0;
            for(int i = 0; i < 5; i++){
                if(table[i] == player[j]){
                    count++;
                }
            }
            if (count == 3){
                int num = int(player[j].getNumber());
                for (int i = 0; i < 4; i++){
                    cards.push_back(Card(i,num));
                }
                return true;
            }
        }
    }
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
    vector<Card> allCards = player;
    allCards.insert(allCards.end(), table.begin(), table.end());
    sort(allCards.begin(), allCards.end(), compareCards);

    int straightCount = 1;
    int currentRank = int(allCards[0].getNumber());
    int currentColor = int(allCards[0].getColor());

    vector<Card> temp;
    temp.push_back(allCards[0]);
    for (int i = 1; i < 7; i++) {
        if (int(allCards[i].getNumber()) == currentRank - 1) {
            if (int(allCards[i].getColor()) == currentColor) {
                straightCount++;
                currentRank--;
                temp.push_back(allCards[i]);
                if (straightCount == 5){
                    if (foundPlayerCard(temp,player)){
                        return true;
                    } else {
                        temp.erase(temp.begin());
                        straightCount--;
                    }
                }
            }
        }
        else {
            temp.clear();
            temp.push_back(allCards[i]);
            straightCount = 1;
            currentRank = int(allCards[i].getNumber());
            currentColor = int(allCards[i].getColor());
        }
    }
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
