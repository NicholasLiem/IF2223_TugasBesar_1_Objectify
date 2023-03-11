#include "lib/GameManager.hpp"
#include "lib/GameState.hpp"
#include "lib/entities/Card.hpp"
#include "lib/entities/Combo.hpp"
#include "lib/states/Next.hpp"
#include "lib/states/PlayerTurn.hpp"

#include <map>
#include <string>
#include <vector>

void contohPerhitunganKartu(GameManager& gameManager)
{
    std::vector<Player>& players = gameManager.getPlayers();
    float highestScore = 0;
    int winnerIndex = 0;
    for (int i = 0; i < players.size(); i++) {
        Player& player = players[i];
        float score = 0;
        std::vector<Card> cards(gameManager.table.takeAll());
        auto playerCards = player.takeAll();
        cards.insert(cards.end(), playerCards.begin(), playerCards.end());
        Combo* combo;
        for (Combo* c : Combo::getCombos()) {
            if (c->isThereCombo(cards)) {
                combo = c->clone();
                score = combo->value();
            } else {
                score = 0; // actually high card value
            }
        }
        if (score > highestScore) {
            highestScore = score;
            winnerIndex = i;
        }
    }
    // update poin pemenang
    players[winnerIndex].setPoints(players[winnerIndex].getPoints() +
                                   gameManager.getPot());
}

int main()
{
    GameManager gameManager;

    gameManager.registerPlayer(Player("budi"));
    gameManager.registerPlayer(Player("udin"));
    gameManager.registerPlayer(Player("dodi"));

    GameState::registerState("player turn", new PlayerTurn);
    GameState::registerState("next", new Next(gameManager));

    GameState* state = GameState::getState("player turn");

    while (!state->isEnd()) {
        state = state->updateState();
    }

    GameState::clearStates();
    return 0;
}
