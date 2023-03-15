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
    std::vector<CangkulPlayer> players;
    std::vector<int> currentRoundTurnQueue;
    std::vector<int> nextRoundTurnQueue;

    int currentPlayerIndex;
    int currentRound;
    int nextRoundFirstPlayerIndex;

    void setupRound();
    void fillDeck();

  public:
    Deck<CangkulCard> deck;
    CangkulTable table;

    CangkulGameManager();

    CangkulPlayer& getCurrentPlayer();
    std::vector<CangkulPlayer>& getPlayers();
    int getCurrentRound() const;

    void registerPlayer(CangkulPlayer player);
    void nextPlayer();
    void setupGame();
    void reset();
};

#endif // !__GAMEMANAGER_
