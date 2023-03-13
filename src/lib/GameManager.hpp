#ifndef __GAMEMANAGER_
#define __GAMEMANAGER_

#include "Card.hpp"
#include "Deck.hpp"
#include "GameState.hpp"
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
    std::vector<int> currentRoundTurnQueue;
    std::vector<int> nextRoundTurnQueue;
    std::map<std::string, Ability*> playerAbilities;

    int currentPlayerIndex;
    int currentRound;
    int nextRoundFirstPlayerIndex;
    int pot;

    bool reversedDirection;

    void setupRound();
    void fillDeck();
    void distributeAbilities();

  public:
    Deck<Card> deck;
    Table table;

    GameManager();
    ~GameManager();

    Player& getCurrentPlayer();
    std::vector<Player>& getPlayers();
    Ability* getAbility(std::string playerNickname);
    int getPot() const;
    int getCurrentRound() const;
    std::vector<int>& getCurrentRoundTurnQueue();
    std::vector<int>& getNextRoundTurnQueue();

    void registerPlayer(Player player);
    void reverseDirection();
    void nextPlayer();
    void setPot(int value);
};

#endif // !__GAMEMANAGER_
