#include "Player.hpp"

#include <algorithm>
#include <vector>

Player::Player(std::string nickname)
{
    this->nickname = nickname;
    points = 0;
}

Player::Player(const Player& other) {
    nickname = other.nickname;
    inventory = other.inventory;
    points = other.points;
}

void Player::setPoints(long points)
{
    this->points = points;
}

void Player::put(Card card)
{
    inventory.push_back(card);
}

Card Player::take(Card card)
{
    auto it = std::find(inventory.begin(), inventory.end(), card);
    if (it != inventory.end()) {
        Card ret = *it;
        inventory.erase(it);
        return ret;
    } else {
        throw "Card not found";
    }
}

std::string Player::getNickname() const
{
    return nickname;
}

long Player::getPoints() const
{
    return points;
}

std::vector<Card> Player::takeAll()
{
    std::vector<Card> ret(inventory);
    clear();
    return ret;
}

Player& Player::operator=(const Player& other)
{
    inventory = other.inventory;
    points = other.points;
    nickname = other.nickname;
    return *this;
}

bool operator==(const Player& a, const Player& b)
{
    return a.getNickname() == b.getNickname();
}

bool operator!=(const Player& a, const Player& b)
{
    return a.getNickname() != b.getNickname();
}
