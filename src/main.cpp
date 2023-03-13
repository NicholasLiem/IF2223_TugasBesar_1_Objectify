#include "Card.hpp"
#include "Combo.hpp"
#include "GameManager.hpp"
#include "GameState.hpp"
#include "Next.hpp"
#include "PlayerTurn.hpp"

#include <map>
#include <string>
#include <vector>

void contohPerhitunganKartu(GameManager& gameManager)
{
    std::vector<Player>& players = gameManager.getPlayers();
    float highestScore = 0;
    int winnerIndex = 0;
    bool isStraightFlush = false;
    // Cek table cards ada bentuk combo apa ga, cek dlu ada straight flush ato engga, kalo iya, isStraightFlush = true
    std::vector<Card> tableCards(gameManager.table.takeAll());

    for (int i = 0; i < players.size(); i++) {
        Player& player = players[i];
        float score = 0;
        std::vector<Card> cards(gameManager.table.takeAll());
        auto playerCards = player.takeAll();
        cards.insert(cards.end(), playerCards.begin(), playerCards.end());
        Combo* combo;
        // Looping sebanyak 12 jenis kombo yang ada
        for (Combo* c : Combo::getCombos()) {
            // Kalau misalnya dari si player ada kombo masuk ke sini, misalnya ada kombo pair
            if (c->isThereCombo(cards)) {
                // Cek di table udah ada belom straight flush, kalo ada, gausah diclone dan gausah di ganti scorenya
                // simpen semua susunan kartu combo ke si combo
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
