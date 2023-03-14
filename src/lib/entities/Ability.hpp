#ifndef __ABILITY_
#define __ABILITY_

#include "Card.hpp"
#include "Deck.hpp"
#include "GameManager.hpp"
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
    Player* owner;
    const std::string name;
    bool used;
    bool muted;

  public:
    Ability(GameManager& game, std::string name);
    virtual ~Ability() = default;
    std::string getName() const;
    Player* getOwner();
    virtual void useAbility() = 0;

    static Deck<Ability*>& getAbilities();
    static void registerAbility(Ability* ability);
    static void clearAbilities();
    void mute();
    void setUsed(bool value);
    void setOwner(Player* player);
    bool isMuted() const;
    bool isUsed() const;
};

class ReRollCard : public Ability
{
  public:
    ReRollCard(GameManager&);
    void useAbility() override;
};

class QuadrupleCard : public Ability
{
  public:
    QuadrupleCard(GameManager&);
    void useAbility() override;
};

class QuarterCard : public Ability
{
  public:
    QuarterCard(GameManager&);
    void useAbility() override;
};

class ReverseDirCard : public Ability
{
  public:
    ReverseDirCard(GameManager&);
    void useAbility() override;
};

class SwapCard : public Ability
{
  public:
    SwapCard(GameManager&);
    void useAbility(Player&, Player&, int, int);

  private:
    void useAbility() override;
};

class SwitchCard : public Ability
{
  public:
    SwitchCard(GameManager&);
    void useAbility(Player&);

  private:
    void useAbility() override;
};

class AbilitylessCard : public Ability
{
  public:
    AbilitylessCard(GameManager&);
    void useAbility(Player&);

  private:
    void useAbility() override;
};

#endif // !__ABILITY_
