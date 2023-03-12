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
    std::map<std::string, Ability> playerAbilities;
    Deck<Card> deck;

    uint currentPlayerIndex;
    uint currentRound;
    uint pot;

    bool reversedDirection;

  public:
    GameManager();

    Player& getCurrentPlayer();
    std::vector<Player>& getPlayers();
    Ability& getAbility(std::string playerNickname);
    uint getPot();
    uint getCurrentRound();

    void registerPlayer(Player player);
    void reverseDirection();
    void nextPlayer();
    void setPot(uint value);

    Table table;
};

#endif // !__GAMEMANAGER_
