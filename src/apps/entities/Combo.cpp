#include "../../lib/entities/Combo.hpp"

vector<Combo*> Combo::combos;

Combo::Combo(string name) : name(name) {}

Combo::Combo(const Combo& other) : name(other.name)
{
    cards = other.cards;
}

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

HighCard::HighCard() : Combo("HighCard") {}

HighCard::HighCard(const HighCard& other) : Combo(other) {}

bool HighCard::isThereCombo(vector<Card>& cards)
{
    if (cards.size() > 0) {
        return true;
    }
    return false;
}

Combo* HighCard::clone()
{
    HighCard* clone = this;
    return clone;
}

Pair::Pair(vector<Card> _cards) : Combo("Pair") {}
Pair::Pair(const Pair& other) : Combo(other) {}

bool Pair::isThereCombo(vector<Card>& cards)
{
    for (int i = 0; i < cards.size(); i++) {
        for (int j = i; j < cards.size(); j++) {
            if (cards[i] == cards[j]) {
                return true;
            }
        }
    }
    return false;
}
Combo* Pair::clone()
{
    Pair* clone = this;
    return clone;
}

TwoPair::TwoPair() : Combo("TwoPair") {}
TwoPair::TwoPair(const TwoPair& other) : Combo(other) {}

bool TwoPair::isThereCombo(vector<Card>& cards)
{
    return false;
}
Combo* TwoPair::clone()
{
    TwoPair* clone = this;
    return this;
}

ThreeOfAKind::ThreeOfAKind() : Combo("ThreeOfAKind") {}
ThreeOfAKind::ThreeOfAKind(const ThreeOfAKind& other) : Combo(other) {}

bool ThreeOfAKind::isThereCombo(vector<Card>& cards)
{
    return false;
}
Combo* ThreeOfAKind::clone()
{
    ThreeOfAKind* clone = this;
    return this;
}

Straight::Straight() : Combo("Straight") {}
Straight::Straight(const Straight& other) : Combo(other) {}

bool Straight::isThereCombo(vector<Card>& cards)
{
    return false;
}
Combo* Straight::clone()
{
    Straight* clone = this;
    return this;
}

Flush::Flush() : Combo("Flush") {}
Flush::Flush(const Flush& other) : Combo(other) {}

bool Flush::isThereCombo(vector<Card>& cards)
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

bool FullHouse::isThereCombo(vector<Card>& cards)
{
    return false;
}
Combo* FullHouse::clone()
{
    FullHouse* clone = this;
    return this;
}

FourOfAKind::FourOfAKind() : Combo("FourOfAKind") {}
FourOfAKind::FourOfAKind(const FourOfAKind& other) : Combo(other) {}

bool FourOfAKind::isThereCombo(vector<Card>& cards)
{
    return false;
}
Combo* FourOfAKind::clone()
{
    FourOfAKind* clone = this;
    return this;
}

StraightFlush::StraightFlush() : Combo("StraightFlush") {}
StraightFlush::StraightFlush(const StraightFlush& other) : Combo(other) {}

bool StraightFlush::isThereCombo(vector<Card>& cards)
{
    return false;
}
Combo* StraightFlush::clone()
{
    StraightFlush* clone = this;
    return this;
}
