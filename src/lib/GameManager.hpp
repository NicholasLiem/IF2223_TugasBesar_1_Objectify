#ifndef __GAMEMANAGER_
#define __GAMEMANAGER_

#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include "Table.hpp"

#include <map>
#include <vector>

// forward declaration
class Ability;

class GameManager
{
  private:
    std::vector<Player> players;
    std::vector<int> playedPlayers;
    std::map<std::string, Ability*> playerAbilities;
    Deck<Card> deck;

    int currentPlayerIndex;
    int currentRound;
    int nextRoundFirstPlayerIndex;
    int pot;

    bool reversedDirection;

    void setupRound();
    void distributeAbilities();

  public:
    GameManager();

    Player& getCurrentPlayer();
    std::vector<Player>& getPlayers();
    Ability& getAbility(std::string playerNickname);
    int getPot() const;
    int getCurrentRound() const;

    void registerPlayer(Player player);
    void reverseDirection();
    void nextPlayer();
    void setPot(int value);

    Table table;
};

#endif // !__GAMEMANAGER_
