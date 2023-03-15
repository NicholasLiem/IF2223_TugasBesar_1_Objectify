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
    std::vector<MainPlayer> players;
    std::vector<int> currentRoundTurnQueue;
    std::vector<int> nextRoundTurnQueue;
    std::map<std::string, Ability*> playerAbilities;

    int currentPlayerIndex;
    int currentRound;
    int nextRoundFirstPlayerIndex;
    long pot;

    void setupRound();
    void fillDeck();
    void distributeAbilities();

  public:
    Deck<MainCard> deck;
    MainTable table;

    GameManager();

    MainPlayer& getCurrentPlayer();
    std::vector<MainPlayer>& getPlayers();
    Ability* getAbility(std::string playerNickname);
    long getPot() const;
    int getCurrentRound() const;
    std::vector<int>& getCurrentRoundTurnQueue();
    std::vector<int>& getNextRoundTurnQueue();

    void registerPlayer(MainPlayer player);
    void reverseDirection();
    void nextPlayer();
    void setPot(long value);
    void setupGame();
    void reset();
};

#endif // !__GAMEMANAGER_
