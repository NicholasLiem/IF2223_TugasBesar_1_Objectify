#ifndef __PLAYER_
#define __PLAYER_

#include "Card.hpp"
#include "InventoryHolder.hpp"

#include <string>

class Player : public InventoryHolder<Card>
{
  private:
    std::string nickname;
    long points;

  public:
    Player(std::string nickname);
    Player(const Player& other);

    void setPoints(long points);
    void put(Card card) override;
    Card take(Card card) override;
    std::vector<Card> takeAll();

    std::string getNickname() const;
    long getPoints() const;
    Card operator-(Card other);
    void operator+(Card other);
    bool operator==(const Player& other);
    bool operator<(const Player& other);
    bool operator>(const Player& other);
    Player& operator=(const Player& other);

    friend bool operator==(const Player& a, const Player& b);
    friend bool operator< (const Player& a, const Player& b);
    friend bool operator> (const Player& a, const Player& b);
    friend bool operator!=(const Player& a, const Player& b);
};

#endif // !__PLAYER_
