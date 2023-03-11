#ifndef __PLAYER_
#define __PLAYER_

#include "Card.hpp"
#include "InventoryHolder.hpp"

#include <string>

class Player : InventoryHolder<Card>
{
  private:
    const std::string nickname;
    long points;

  public:
    Player(std::string nickname);

    void setPoints(long points);
    void put(Card card) override;
    Card take(Card card) override;

    std::string getNickname() const;
    int getPoints() const;
};

#endif // !__PLAYER_
