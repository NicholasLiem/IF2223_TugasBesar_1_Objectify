#include "Table.hpp"
#include <iostream>

template <class T,class U>
std::vector<Card<T,U>> Table<T,U>::takeAll()
{
    std::vector<Card<T,U>> cards;
    for (auto card : this->inventory)
    {
        cards.push_back(card);
    }
    this->inventory.clear();
    return cards;
}

template <class T,class U>
void Table<T,U>::put(Card<T,U> card)
{
    this->inventory.push_back(card);
}

template <class T,class U>
Card<T,U> Table<T,U>::take(Card<T,U> card)
{
    for (auto it = this->inventory.begin(); it != this->inventory.end(); it++)
    {
        if (*it == card)
        {
            this->inventory.erase(it);
                return card;
        }
    }
    throw "Card not found";
}

template class Table<CardColor,CardNumber>;
template class Table<CardSymbol,CangkulNumber>;