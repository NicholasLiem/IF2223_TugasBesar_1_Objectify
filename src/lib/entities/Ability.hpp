#ifndef __ABILITY_
#define __ABILITY_

#include "Card.hpp"
#include "GameManager.hpp"
#include "Player.hpp"

#include <string>

// forward declaration
class GameManager;

class Ability
{
  protected:
    GameManager& game;
    Player& owner;
    bool used;
    bool muted;

  public:
    Ability(GameManager& game, Player& owner);
    virtual void useAbility() = 0;
};

class ReRollCard : public Ability
{
  public:
    ReRollCard(GameManager&, Player&);
    void useAbility();
};

class QuadrupleCard : public Ability
{
  public:
    QuadrupleCard(GameManager&, Player&);
    void useAbility();
};

class QuarterCard : public Ability
{
  public:
    QuarterCard(GameManager&, Player&);
    void useAbility();
};

class ReverseDirCard : public Ability
{
  public:
    ReverseDirCard(GameManager&, Player&);
    void useAbility();
};

class SwapCard : public Ability
{
  public:
    SwapCard(GameManager&, Player&);
    void useAbility(Player&);
};

class SwitchCard : public Ability
{
  public:
    SwitchCard(GameManager&, Player&);
    void useAbility(Player&);
};

class AbilityLessCard : public Ability
{
  public:
    AbilityLessCard(GameManager&, Player&);
    void useAbility();
};

#endif // !__ABILITY_
