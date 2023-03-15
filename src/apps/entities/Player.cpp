#include "Player.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

template <class T, class U>
Player<T, U>::Player(std::string nickname)
{
    this->nickname = nickname;
    points = 0;
}

template <class T, class U>
Player<T, U>::Player(const Player& other)
{
    nickname = other.nickname;
    inventory = other.inventory;
    points = other.points;
}

template <class T, class U>
void Player<T, U>::setPoints(long points)
{
    this->points = points;
}

template <class T, class U>
void Player<T, U>::put(Card<T, U> card)
{
    inventory.push_back(card);
}

template <class T, class U>
Card<T, U> Player<T, U>::take(Card<T, U> card)
{
    auto it = std::find(inventory.begin(), inventory.end(), card);
    if (it != this->inventory.end()) {
        Card<T, U> ret = *it;
        inventory.erase(it);
        return ret;
    } else {
        throw "Card not found";
    }
}

template <class T, class U>
std::string Player<T, U>::getNickname() const
{
    return nickname;
}

template <class T, class U>
long Player<T, U>::getPoints() const
{
    return points;
}

template <class T, class U>
std::vector<Card<T, U>> Player<T, U>::takeAll()
{
    std::vector<Card<T, U>> ret(inventory);
    inventory.clear();
    return ret;
}

template <class T, class U>
bool Player<T, U>::hasTypeCard(Card<T, U> tableCard) const
{
    T tableCardType = tableCard.getColor();
    for (auto card : inventory) {
        if (card.getColor() == tableCardType) {
            return true;
        }
    }
    return false;
}

template <class T, class U>
void Player<T, U>::printInventory()
{
    int count = 1;
    for(int i = 0; i < inventory.size(); i++) {
        std::cout << count << ". " << this->inventory[i] << std::endl;
        count++;
    }
}

template class Player<CardColor, CardNumber>;
template class Player<CardSymbol, CangkulNumber>;
