#ifndef __ABILITY_
#define __ABILITY_

#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"

#include <string>
#include <vector>

// forward declaration
class GameManager;

class Ability
{
  private:
    static Deck<Ability*> abilities;

  protected:
    GameManager& game;
    Player& owner;
    const std::string name;

  public:
    Ability(GameManager& game, Player& owner);
    std::string getName() const;
    const Player& getOwner() const;
    virtual void useAbility() = 0;

    static Deck<Ability*>& getAbilities();
    static void registerAbility(Ability* ability);
    static void clearAbilities();
};

#endif // !__ABILITY_
