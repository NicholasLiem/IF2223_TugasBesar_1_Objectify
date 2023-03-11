#ifndef __ABILITY_
#define __ABILITY_

// forward declaration
class GameManager;

#include "Card.hpp"
#include "Player.hpp"

class Ability
{
  protected:
    GameManager& game;
    Player& owner;

  public:
    Ability(GameManager& game, Player& owner);
    virtual void useAbility() = 0;
};

#endif // !__ABILITY_
