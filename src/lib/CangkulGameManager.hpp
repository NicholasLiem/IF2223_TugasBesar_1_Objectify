#ifndef __CANGKULGAMEMANAGER_
#define __CANGKULGAMEMANAGER_

#include "Card.hpp"
#include "Deck.hpp"
#include "GameState.hpp"
#include "Player.hpp"
#include "Table.hpp"

#include <map>
#include <vector>

class CangkulGameManager
{
  private:
    std::vector<Player> players;
    std::vector<int> currentRoundTurnQueue;
    std::vector<int> nextRoundTurnQueue;

    int currentPlayerIndex;
    int currentRound;
    int nextRoundFirstPlayerIndex;

    void setupRound();
    void fillDeck();

  public:
    Deck<Card> deck;
    Table table;

    CangkulGameManager();

    Player& getCurrentPlayer();
    std::vector<Player>& getPlayers();
    int getCurrentRound() const;

    void registerPlayer(Player player);
    void nextPlayer();
    void setupGame();
    void reset();
};

#endif // !__GAMEMANAGER_
