#include "../../lib/entities/Combo.hpp"

Combo::Combo(string name) : name(name) {}

Combo::Combo(Combo& other) : name(other.name) {}

void Combo::registerCombo(Combo* combo){
    combos.push_back(combo);
}

void Combo::clearCombos(){
    combos.clear();
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
    
}

Pair::Pair(vector<Card> _cards) : Combo("Pair") {}
bool Pair::isThereCombo(vector<Card>& cards) {}
Combo* Pair::clone() {}

TwoPair::TwoPair(vector<Card> _cards) : Combo("TwoPair") {}
bool TwoPair::isThereCombo(vector<Card>& cards) {}
Combo* TwoPair::clone() {}

ThreeOfAKind::ThreeOfAKind(vector<Card> _cards) : Combo("ThreeOfAKind"){}
bool ThreeOfAKind::isThereCombo(vector<Card>& cards) {}
Combo* ThreeOfAKind::clone() {}

Straight::Straight(vector<Card> _cards) : Combo("Straight"){}
bool Straight::isThereCombo(vector<Card>& cards) {}
Combo* Straight::clone() {}

Flush::Flush(vector<Card> _cards) : Combo("Flush") {}
bool Flush::isThereCombo(vector<Card>& cards) {}
Combo* Flush::clone() {}

FullHouse::FullHouse(vector<Card> _cards) : Combo("FullHouse"){}
bool FullHouse::isThereCombo(vector<Card>& cards) {}
Combo* FullHouse::clone() {}

FourOfAKind::FourOfAKind(vector<Card> _cards) : Combo("FourOfAKind") {}
bool FourOfAKind::isThereCombo(vector<Card>& cards) {}
Combo* FourOfAKind::clone() {}

StraightFlush::StraightFlush(vector<Card> _cards) : Combo("StraightFlush") {}
bool StraightFlush::isThereCombo(vector<Card>& cards) {}
Combo* StraightFlush::clone() {}