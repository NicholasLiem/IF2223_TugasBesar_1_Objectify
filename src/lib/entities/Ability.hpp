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
    virtual void mute();
};

class ReRollCard : public Ability
{
  public:
    ReRollCard(GameManager&, Player&);
    void useAbility();
    void mute();
};

class QuadrupleCard : public Ability
{
  public:
    QuadrupleCard(GameManager&, Player&);
    void useAbility();
    void mute();
};

class QuarterCard : public Ability
{
  public:
    QuarterCard(GameManager&, Player&);
    void useAbility();
    void mute();
};

class ReverseDirCard : public Ability
{
  public:
    ReverseDirCard(GameManager&, Player&);
    void useAbility();
    void mute();
};

class SwapCard : public Ability
{
  public:
    SwapCard(GameManager&, Player&);
    void useAbility(Player&);
    void mute();
};

class SwitchCard : public Ability
{
  public:
    SwitchCard(GameManager&, Player&);
    void useAbility(Player&);
    void mute();
};

class AbilitylessCard : public Ability
{
  public:
    AbilitylessCard(GameManager&, Player&);
    void useAbility();
    void mute();
};

#endif // !__ABILITY_
