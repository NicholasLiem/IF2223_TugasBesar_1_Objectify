#include "Player.hpp"

#include <algorithm>
#include <vector>

Player::Player(std::string nickname) : nickname(nickname) {}

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
        return *it;
    } else {
        throw "Card not found";
    }
}

std::string Player::getNickname() const
{
    return nickname;
}

int Player::getPoints() const
{
    return points;
}

std::vector<Card> Player::takeAll()
{
    std::vector<Card> ret(inventory);
    clear();
    return ret;
}

bool operator==(const Player& a, const Player& b) {
    return a.getNickname() == b.getNickname();
}

bool operator!=(const Player& a, const Player& b) {
    return a.getNickname() != b.getNickname();
}
