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
    const std::string name;
    bool used;
    bool muted;

  public:
    Ability(GameManager& game, Player& owner);
    virtual void useAbility() = 0;
    void mute();
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
    void useAbility(Player&, int, int);
};

class SwitchCard : public Ability
{
  public:
    SwitchCard(GameManager&, Player&);
    void useAbility(Player&);
};

class AbilitylessCard : public Ability
{
  public:
    AbilitylessCard(GameManager&, Player&);
    void useAbility(Player&);
};

#endif // !__ABILITY_
