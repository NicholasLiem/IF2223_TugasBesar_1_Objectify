#ifndef __ABILITY_
#define __ABILITY_

#include "Card.hpp"
#include "Player.hpp"

#include <string>

// forward declaration
class GameManager;

class Ability
{
  protected:
    GameManager& game;
    Player& owner;
    const std::string name;

  public:
    Ability(GameManager& game, Player& owner);
    std::string getName() const;
    virtual void useAbility() = 0;
};

#endif // !__ABILITY_
