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
    int nextTurnPlayerIndex;
    int nilaiKartuTertinggi;

    void setupRound();
    void fillDeck();

  public:
    Deck<CangkulCard> deck;
    CangkulTable table;

    CangkulGameManager();

    int getNextTurnPlayerIndex();
    void setNextTurnPlayerIndex(int a);

    int getNilaiKartuTertinggi();
    void setNilaiKartuTertinggi(int a);

    int getCurrentPlayerIndex();

    CangkulPlayer& getCurrentPlayer();
    std::vector<CangkulPlayer>& getPlayers();
    int getCurrentRound() const;

    void registerPlayer(CangkulPlayer player);
    void nextPlayer();
    void setupGame();
    void reset();
};

#endif // !__GAMEMANAGER_
