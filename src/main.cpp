#include "Ability.hpp"
#include "Action.hpp"
#include "Card.hpp"
#include "Combo.hpp"
#include "GameManager.hpp"
#include "GameState.hpp"
#include "State.hpp"

#include <map>
#include <string>
#include <vector>

// void contohPerhitunganKartu(GameManager& gameManager)
// {
//     std::vector<Player>& players = gameManager.getPlayers();
//     float highestScore = 0;
//     int winnerIndex = 0;
//     for (int i = 0; i < players.size(); i++) {
//         Player& player = players[i];
//         float score = 0;
//         std::vector<Card> cards(gameManager.table.takeAll());
//         auto playerCards = player.takeAll();
//         cards.insert(cards.end(), playerCards.begin(), playerCards.end());
//         Combo* combo;
//         for (Combo* c : Combo::getCombos()) {
//             if (c->isThereCombo(cards)) {
//                 combo = c->clone();
//                 score = combo->value();
//             } else {
//                 score = 0; // actually high card value
//             }
//         }
//         if (score > highestScore) {
//             highestScore = score;
//             winnerIndex = i;
//         }
//     }
//     // update poin pemenang
//     players[winnerIndex].setPoints(players[winnerIndex].getPoints() +
//                                    gameManager.getPot());
// }

int main()
{
    GameManager gameManager;

    GameState::registerState("dashboard", new Dashboard(gameManager));
    GameState::registerState("player turn", new PlayerTurn);
    GameState::registerState("next", new Next(gameManager));
    GameState::registerState("player registration",
                             new PlayerRegistration(gameManager));
    GameState::registerState("reverse", new ReverseDirAct(gameManager));
    GameState::registerState("re-roll", new ReRollAct(gameManager));
    GameState::registerState("double", new Double(gameManager));
    GameState::registerState("half", new Half(gameManager));
    GameState::registerState("quarter", new QuarterAct(gameManager));
    GameState::registerState("quadruple", new QuadrupleAct(gameManager));
    GameState::registerState("switch", new SwitchAct(gameManager));
    GameState::registerState("swap", new SwapAct(gameManager));
    GameState::registerState("abilityless", new AbilitylessAct(gameManager));
    GameState::registerState("scoreboard", new Scoreboard(gameManager));
    GameState::registerState("calculation", new CardCalculation(gameManager));
    GameState::registerState("conclusion", new Conclusion(gameManager));
    GameState::registerState("end", new End);

    Ability::registerAbility(new QuadrupleCard(gameManager));
    Ability::registerAbility(new QuarterCard(gameManager));
    Ability::registerAbility(new ReRollCard(gameManager));
    Ability::registerAbility(new ReverseDirCard(gameManager));
    Ability::registerAbility(new SwapCard(gameManager));
    Ability::registerAbility(new SwitchCard(gameManager));
    Ability::registerAbility(new AbilitylessCard(gameManager));

    Combo::registerCombo(new HighCard());
    Combo::registerCombo(new Pair());
    Combo::registerCombo(new TwoPair());
    Combo::registerCombo(new ThreeOfAKind());
    Combo::registerCombo(new Straight());
    Combo::registerCombo(new Flush());
    Combo::registerCombo(new FullHouse());
    Combo::registerCombo(new FourOfAKind());
    Combo::registerCombo(new StraightFlush());

    GameState* state = GameState::getState("player registration");

    while (!state->isEnd()) {
        state = state->updateState();
    }

    GameState::clearStates();
    Ability::clearAbilities();
    Combo::clearCombos();

    return 0;
}
