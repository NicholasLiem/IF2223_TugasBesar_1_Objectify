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
    std::vector<Player<CardSymbol, CangkulNumber>> players;
    std::vector<int> currentRoundTurnQueue;
    std::vector<int> nextRoundTurnQueue;

    int currentPlayerIndex;
    int currentRound;
    int nextRoundFirstPlayerIndex;

    void setupRound();
    void fillDeck();

  public:
    Deck<Card<CardSymbol, CangkulNumber>> deck;
    Table<CardSymbol, CangkulNumber> table;

    CangkulGameManager();

    Player<CardSymbol, CangkulNumber>& getCurrentPlayer();
    std::vector<Player<CardSymbol, CangkulNumber>>& getPlayers();
    int getCurrentRound() const;

    void registerPlayer(Player<CardSymbol, CangkulNumber> player);
    void nextPlayer();
    void setupGame();
    void reset();
};

#endif // !__GAMEMANAGER_
