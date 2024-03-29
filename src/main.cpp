#include "Ability.hpp"
#include "Action.hpp"
#include "CangkulGameManager.hpp"
#include "CangkulState.hpp"
#include "Card.hpp"
#include "Combo.hpp"
#include "GameManager.hpp"
#include "GameState.hpp"
#include "State.hpp"
#include "Utils.hpp"

#include <map>
#include <string>
#include <vector>

int main()
{
    string game;
    Utils::clear_screen();
    Utils::splash_screen();
    std::cout << "Apakah anda ingin memainkan permainan kompetisi Kartu ala "
                 "Kerajaan Permen? (\e[1;32mYa\e[0m/\e[1;31mTidak\e[0m): \n";
    std::cout << "> ";
    std::getline(std::cin, game);
    std::cout << std::endl;
    if (Utils::to_lower(game) == "ya") {
        GameManager gameManager;

        GameState::registerState("dashboard", new Dashboard(gameManager));
        GameState::registerState("player turn", new PlayerTurn(gameManager));
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
        GameState::registerState("abilityless",
                                 new AbilitylessAct(gameManager));
        GameState::registerState("scoreboard", new Scoreboard(gameManager));
        GameState::registerState("calculation",
                                 new CardCalculation(gameManager));
        GameState::registerState("conclusion", new Conclusion(gameManager));
        GameState::registerState("help", new HelpCommand(gameManager));
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
        // final state
        state->updateState();

        GameState::clearStates();
        Ability::clearAbilities();
        Combo::clearCombos();
    } else {
        CangkulGameManager gameManager;

        GameState::registerState("dashboard",
                                 new CangkulDashboard(gameManager));
        GameState::registerState("player turn",
                                 new CangkulPlayerTurn(gameManager));
        GameState::registerState("player registration",
                                 new CangkulPlayerRegistration(gameManager));
        GameState::registerState("draw card", new CangkulDrawCard(gameManager));
        GameState::registerState("conclusion",
                                 new CangkulConclusion(gameManager));
        GameState::registerState("pilih kartu",
                                 new CangkulPilihKartu(gameManager));
        GameState::registerState("next turn",
                                 new CangkulNextPlayer(gameManager));
        GameState::registerState("winner pick card",
                                 new CangkulWinnerPickCard(gameManager));
        GameState::registerState("end", new End);

        GameState* state = GameState::getState("player registration");

        while (!state->isEnd()) {
            state = state->updateState();
        }
        // final state
        state->updateState();

        GameState::clearStates();
    }
    // final state
    // state->updateState();

    return 0;
}
