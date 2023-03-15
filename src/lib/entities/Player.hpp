#ifndef __PLAYER_
#define __PLAYER_

#include "Card.hpp"
#include "InventoryHolder.hpp"

#include <string>

template <class T, class U>
class Player : public InventoryHolder<Card<T, U>>
{
  private:
    std::string nickname;
    long points;

  public:
    Player(std::string nickname);
    Player(const Player<T, U>& other);

    void setPoints(long points);
    void put(Card<T, U> card) override;
    Card<T, U> take(Card<T, U> card) override;
    std::vector<Card<T, U>> takeAll();

    std::string getNickname() const;
    long getPoints() const;

    Card<T, U> operator-(Card<T, U> other)
    {
        return take(other);
    }

    void operator+(Card<T, U> other)
    {
        put(other);
    }

    Player<T, U>& operator=(const Player<T, U>& other)
    {
        this->inventory = other.inventory;
        this->nickname = other.nickname;
        this->points = other.points;
        return *this;
    }

    friend bool operator==(const Player<T, U>& a, const Player<T, U>& b)
    {
        return a.getNickname() == b.getNickname();
    }

    friend bool operator<(const Player<T, U>& a, const Player<T, U>& b)
    {
        return a.getPoints() < b.getPoints();
    }

    friend bool operator>(const Player<T, U>& a, const Player<T, U>& b)
    {
        return a.getPoints() > b.getPoints();
    }

    friend bool operator!=(const Player<T, U>& a, const Player<T, U>& b)
    {
        return a.getNickname() != b.getNickname();
    }

    bool hasTypeCard(Card<T, U> card) const;
    void printInventory();
};

typedef Player<CardColor, CardNumber> MainPlayer;
typedef Player<CardSymbol, CangkulNumber> CangkulPlayer;

#endif // !__PLAYER_
