#include "../../lib/entities/Combo.hpp"
using namespace std;

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

bool compareColor(const Card& a,const Card& b){
    return a.getColor() > b.getColor();
}

bool isMember(vector<Card>& cards, Card card){
    for (int i = 0; i < cards.size(); i++){
        if (cards[i].value() == card.value()){
            return true;
        }
    }
    return false;
}

bool foundPlayerCard(vector<Card>& temp, vector<Card>& player){
    for (int j = 0; j < 2; j++){
        if(isMember(temp,player[j])){
            return true;
        }
    }
    return false;
}

// Implementation of Class HighCard
HighCard::HighCard() : Combo("HighCard") {}

HighCard::HighCard(const HighCard& other) : Combo(other) {}

bool HighCard::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    if (player.size() > 0) {
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
    std::sort(player.begin(),player.end(),compareCards);
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
    float val = 1.39 + float(cards[0].getNumber()) * 1000 + float(cards[0].getColor()) * 0.003 + float(cards[1].getNumber()) * 10 + float(cards[1].getColor()) * 0.0003;
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
    val += float(cards[0].getNumber()) * 1000 + float(cards[0].getColor()) * 0.00003 + float(cards[1].getColor()) * 0.000003;
    val += float(cards[2].getNumber()) * 10 + float(cards[2].getColor()) * 0.0000003 + float(cards[3].getColor()) * 0.00000003;
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
    return 26261.39969696 + float(cards[0].getNumber()) * 100000 + float(cards[0].getColor()) * 0.000000003 + float(cards[1].getColor()) * 0.0000000003 + float(cards[2].getColor()) * 0.00000000003;
}

Straight::Straight() : Combo("Straight") {}
Straight::Straight(const Straight& other) : Combo(other) {}

bool Straight::isThereCombo(vector<Card>& player, vector<Card>& table) {
    vector<Card> allCards = player;
    allCards.insert(allCards.end(), table.begin(), table.end());
    sort(allCards.begin(), allCards.end(), compareCards);

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
                    cards.insert(cards.begin(),temp.begin(),temp.end());
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
    cout << cards.size() << endl;
    // val maks = 2626261.3996969696399996
    float val = 1326261.39969696963 + float(cards[0].getNumber()) * 100000;
    float constant = 0.000000000003 ;
    for (int i = 0; i < 5; i++){
        val += float(cards[i].getColor())*constant;
        constant /= 10;
    }
    return val;
}

Flush::Flush() : Combo("Flush") {}
Flush::Flush(const Flush& other) : Combo(other) {}

bool Flush::isThereCombo(vector<Card>& player, vector<Card>& table)
{
    vector<Card> allCards = player;
    allCards.insert(allCards.end(), table.begin(), table.end());
    sort(allCards.begin(), allCards.end(),compareCards);

    vector<Card> temp1;
    vector<Card> temp2;
    vector<Card> temp3;
    vector<Card> temp4;
    for (int i = 0; i < 7; i++) {
        switch(int(allCards[i].getColor())){
            case 0:
                temp1.push_back(allCards[i]);
            case 1:
                temp2.push_back(allCards[i]);
            case 2:
                temp3.push_back(allCards[i]);
            case 3:
                temp4.push_back(allCards[i]);
        }
    }

    if (temp1.size() > 4){
        cards.insert(cards.begin(),temp1.begin(),temp1.begin()+5);
        if (foundPlayerCard(cards,player)){
            return true;
        } else {
            if (temp1.size() > 5){
                cards.erase(cards.begin());
                cards.push_back(temp1[5]);
                return true;
            } else {
                return false;
            }
        }
    } else if (temp2.size() > 4){
        cards.insert(cards.begin(),temp2.begin(),temp2.begin()+5);
        if (foundPlayerCard(cards,player)){
            return true;
        } else {
            if (temp2.size() > 5){
                cards.erase(cards.begin());
                cards.push_back(temp2[5]);
                return true;
            } else {
                return false;
            }
        }
    } else if (temp3.size() > 4){
        cards.insert(cards.begin(),temp3.begin(),temp3.begin()+5);
        if (foundPlayerCard(cards,player)){
            return true;
        } else {
            if (temp3.size() > 5){
                cards.erase(cards.begin());
                cards.push_back(temp3[5]);
                return true;
            } else {
                return false;
            }
        }
    } else if (temp4.size() > 4){
        cards.insert(cards.begin(),temp4.begin(),temp4.begin()+5);
        if (foundPlayerCard(cards,player)){
            return true;
        } else {
            if (temp4.size() > 5){
                cards.erase(cards.begin());
                cards.push_back(temp4[5]);
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

float Flush::value() const {
    // max value = 13133939391.39969696963999969
    float val = 2626261.3996969696399996 + float(cards[0].getColor())*0.00000000000000003;
    int constant = 10;
    for (int i = 4; i >= 0; i--){
        val += float(cards[i].getNumber())*constant;
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
    float val = 13133939391.39969696963999969 + float(cards[0].getNumber())*1000000000 + float(cards[3].getNumber())*10000000;
    float constant = 0.000000000000000003;
    for (int i = 0; i < 5; i++){
        val += float(cards[i].getColor())*constant;
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
    float val = 26263939391.3996969696399996996396 + float(cards[0].getNumber())*1000000;
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
    vector <Card> green;
    vector <Card> blue;
    vector <Card> yellow;
    vector <Card> red;
    vector <Card> allCards;
    allCards.insert(allCards.end(),table.begin(),table.end());
    allCards.insert(allCards.end(),player.begin(),player.end());
    for(int i = 0; i < allCards.size();i++){
        switch ((int)allCards[i].getColor())
        {
        case 0:
            green.push_back(allCards[i]);
            break;
        case 1 : 
            blue.push_back(allCards[i]);
            break;
        case 2 : 
            yellow.push_back(allCards[i]);
            break;
        case 3 : 
            red.push_back(allCards[i]);
            break;
        default:
            break;
        }
    }
    allCards.clear();
    if(green.size() < 5 && blue.size()< 5 && yellow.size() < 5 && red.size() < 5){
        return false;
    }
    else if(green.size() >= 5){
        allCards.insert(allCards.end(),green.begin(),green.end());
    }else if(blue.size() >= 5){
        allCards.insert(allCards.end(),blue.begin(),blue.end());
    }else if(yellow.size() >= 5){
        allCards.insert(allCards.end(),yellow.begin(),yellow.end());
    }else{
        allCards.insert(allCards.end(),red.begin(),red.end());
    }

    bool inPlayer = false;
    for(int i = 0; i < player.size();i++){
        if(isMember(allCards,player[i])){
            inPlayer = true;
            break;
        }
    }
    if(!inPlayer){
        return false;
    }
    // Mengurutkan seluruh kartu yang ada dan diurutkan  (12,11,10,9,8,7) -> 7 kartu player, sisanya meja
    sort(allCards.begin(),allCards.end(),compareCards);
    vector<Card> temp;
    temp.push_back(allCards[0]);
    int straightCount = 1;
    int currentRank = (int)allCards[0].getNumber();
    for (int i = 1; i < allCards.size(); i++) {
        if (int(allCards[i].getNumber()) == currentRank - 1) {
            straightCount++;
            currentRank--;
            temp.push_back(allCards[i]);
            if (straightCount == 5){
                if (foundPlayerCard(temp,player)){
                    cards.insert(cards.begin(),temp.begin(),temp.end());
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

float StraightFlush::value() const {
    // max value = 39393939391.39969696963999969963969
    float val = 26393939391.3996969696399996996396 + float(cards[0].getNumber())*100000000 + float(cards[0].getColor())*0.00000000000000000000003;
    return val;
}

Combo* StraightFlush::clone()
{
    StraightFlush* clone = this;
    return new StraightFlush(*this);
}
