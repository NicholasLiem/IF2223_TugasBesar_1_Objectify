#include "../../lib/entities/Table.hpp"
#include <iostream>

Table::Table()
{
}

std::vector<Card> Table::takeAll()
{
    std::vector<Card> cards;
    for (auto card : this->inventory)
    {
        cards.push_back(card);
    }
    this->inventory.clear();
    return cards;
}

void Table::put(Card card)
{
    this->inventory.push_back(card);
}

Card Table::take(Card card)
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