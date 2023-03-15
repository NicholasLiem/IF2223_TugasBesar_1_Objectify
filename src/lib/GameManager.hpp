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
    std::vector<Player<CardColor,CardNumber>> players;
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
    Deck<Card<CardColor,CardNumber>> deck;
    Table<CardColor,CardNumber> table;

    GameManager();

    Player<CardColor,CardNumber>& getCurrentPlayer();
    std::vector<Player<CardColor,CardNumber>>& getPlayers();
    Ability* getAbility(std::string playerNickname);
    long getPot() const;
    int getCurrentRound() const;
    std::vector<int>& getCurrentRoundTurnQueue();
    std::vector<int>& getNextRoundTurnQueue();

    void registerPlayer(Player<CardColor,CardNumber> player);
    void reverseDirection();
    void nextPlayer();
    void setPot(long value);
    void setupGame();
    void reset();
};

#endif // !__GAMEMANAGER_
