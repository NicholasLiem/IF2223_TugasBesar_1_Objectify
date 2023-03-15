#include "Player.hpp"

#include <algorithm>
#include <vector>

template <class T, class U>
Player<T,U>::Player(std::string nickname)
{
    this->nickname = nickname;
    points = 0;
}

template <class T, class U>
Player<T,U>::Player(const Player& other) {
    nickname = other.nickname;
    this->inventory = other.inventory;
    points = other.points;
}

template <class T, class U>
void Player<T,U>::setPoints(long points)
{
    this->points = points;
}

template <class T, class U>
void Player<T,U>::put(Card<T,U> card)
{
    this->inventory.push_back(card);
}

template <class T, class U>
Card<T,U> Player<T,U>::take(Card<T,U> card)
{
    auto it = std::find(this->inventory.begin(), this->inventory.end(), card);
    if (it != this->inventory.end()) {
        Card<T,U> ret = *it;
        this->inventory.erase(it);
        return ret;
    } else {
        throw "Card not found";
    }
}

template <class T, class U>
std::string Player<T,U>::getNickname() const
{
    return nickname;
}

template <class T, class U>
long Player<T,U>::getPoints() const
{
    return points;
}

template <class T, class U>
std::vector<Card<T,U>> Player<T,U>::takeAll()
{
    std::vector<Card<T,U>> ret(this->inventory);
    ret.clear();
    return ret;
}

template <class T, class U>
Card<T,U> Player<T,U>::operator-(Card<T,U> other){
    return Player<T,U>::take(other);
}

template <class T, class U>
void Player<T,U>::operator+(Card<T,U> other){
    Player<T,U>::put(other);
}

template <class T, class U>
bool Player<T,U>::operator==(const Player<T,U>& other){
    return (this->getNickname() == other.getNickname());
}

template <class T, class U>
bool Player<T,U>::operator<(const Player<T,U>& other){
    return this->getPoints() < other.getPoints();
}

template <class T, class U>
bool Player<T,U>::operator>(const Player<T,U>& other){
    return this->getPoints() > other.getPoints();
}

template <class T, class U>
Player<T,U>& Player<T,U>::operator=(const Player<T,U>& other)
{
    this->inventory = other.inventory;
    points = other.points;
    nickname = other.nickname;
    return *this;
}

template <class T, class U>
bool operator==(const Player<T,U>& a, const Player<T,U>& b)
{
    return a.getNickname() == b.getNickname();
}

bool operator==(const Player<CardColor,CardNumber>& a, const Player<CardColor,CardNumber>& b)
{
    return a.getNickname() == b.getNickname();
}
template <class T, class U>
bool operator<(const Player<T,U>& a, const Player<T,U>& b){
    return a.getPoints() < b.getPoints();
}

template <class T, class U>
bool operator>(const Player<T,U>&a, const Player<T,U>& b){
    return a.getPoints() > b.getPoints();
};

template <class T, class U>
bool operator!=(const Player<T,U>& a, const Player<T,U>& b)
{
    return a.getNickname() != b.getNickname();
}

bool operator!=(const Player<CardColor,CardNumber>& a, const Player<CardColor,CardNumber>& b)
{
    return a.getNickname() != b.getNickname();
}

template class Player<CardColor,CardNumber>;
template class Player<CardSymbol,CangkulNumber>;