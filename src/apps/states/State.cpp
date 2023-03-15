#include "State.hpp"

#include "Ability.hpp"
#include "Action.hpp"
#include "Combo.hpp"
#include "Exceptions.hpp"
#include "GameState.hpp"
#include "Utils.hpp"

#include <iostream>
#include <string>
#include <vector>

std::string to_lower(std::string s)
{
    std::string result;
    for (auto it = s.begin(); it != s.end(); it++) {
        result.push_back(std::tolower(*it));
    }
    return result;
}

void print_leaderboard(GameManager& gm) {}

Dashboard::Dashboard(GameManager& gm) : GameState(false), gameManager(gm) {}

GameState* Dashboard::updateState()
{
    if (gameManager.getCurrentRound() == 6) {
        return GameState::getState("calculation");
    }
    std::cout << "\e[1;93mRonde ke-" << gameManager.getCurrentRound()
              << "\e[0m\nPoin hadiah: " << gameManager.getPot()
              << "\nKartu di meja:\n";
    int i = 1;
    for (const MainCard& c : gameManager.table.getAll()) {
        std::cout << "\t" << i++ << ". " << c << "\n";
    }
    const MainPlayer& player = gameManager.getCurrentPlayer();
    std::cout << "Nama pemain: \e[1;93m" << player.getNickname()
              << "\e[0m\nKartu di tangan:\n\t1. " << player.get(0) << "\n\t2. "
              << player.get(1) << "\n";
    if (gameManager.getAbility(player.getNickname()) != NULL) {
        Ability& ability = *gameManager.getAbility(player.getNickname());
        std::cout << "Kamu punya \e[1;92m" << ability.getName() << "\e[0m"
                  << std::endl;
    }
    return GameState::getState("player turn");
}

PlayerTurn::PlayerTurn(GameManager& game) : GameState(false), gameManager(game)
{
}

GameState* PlayerTurn::updateState()
{
    std::string command;
    std::cout << "> ";
    std::getline(std::cin >> std::ws, command);

    try {
        try {
            GameState* nextState = GameState::getState(to_lower(command));
            int round = gameManager.getCurrentRound();
            if (round == 1) {
                if (to_lower(command) == "re-roll" ||
                    to_lower(command) == "quadruple" ||
                    to_lower(command) == "quarter" ||
                    to_lower(command) == "reverse" ||
                    to_lower(command) == "swapcard" ||
                    to_lower(command) == "switch" ||
                    to_lower(command) == "abilityless") {
                    throw AccessAbilityException(command);
                }
            }
            if (dynamic_cast<Action*>(nextState)) {
                return nextState;
            } else {
                throw InvalidActionException(command);
            }
        } catch (std::out_of_range) {
            throw InvalidActionException(command);
        } catch (AccessAbilityException& e) {
            std::cout << e.what() << "\n";
            return GameState::getState("player turn");
        }
    } catch (InvalidActionException& e) {
        std::cout << e.what() << "\n";
        return GameState::getState("player turn");
    }
}

PlayerRegistration::PlayerRegistration(GameManager& gameManager)
    : GameState(false), gameManager(gameManager)
{
}

GameState* PlayerRegistration::updateState()
{
    std::string first;
    for (int i = 1; i <= 7;) {
        std::string name;
        std::cout << "Masukkan nickname player " << i << ": ";
        std::cin >> name;
        try {
            gameManager.registerPlayer(MainPlayer(name));
            std::cout << "Player " << i
                      << " \e[1;93m" + name + "\e[0m telah terdaftar!"
                      << std::endl;
        } catch (const std::string& exception) {
            std::cout << exception << "\n";
            continue;
        }
        if (i == 1) {
            first = name;
        }
        i++;
    }
    std::cout << "Giliran pertama diambil oleh \e[1;93m" << first << "\e[0m"
              << std::endl;
    return GameState::getState("dashboard");
}

CardCalculation::CardCalculation(GameManager& gm)
    : GameState(false), gameManager(gm)
{
}

GameState* CardCalculation::updateState()
{
    std::cout << "\e[1;93mSaatnya perhitungan kartu!\e[0m\n";
    std::vector<Combo*>& combos = Combo::getCombos();
    std::vector<Combo*> playerCombos;
    std::vector<MainPlayer>& players = gameManager.getPlayers();
    std::vector<MainCard> tableCards = gameManager.table.takeAll();
    for (MainPlayer& p : players) {
        std::vector<MainCard> playerCards = p.takeAll();
        Combo* strongestCombo = new HighCard;
        float value = 0;
        for (Combo* combo : combos) {
            if (combo->isThereCombo(playerCards, tableCards)) {
                if (combo->value() > value) {
                    Combo* tmp = strongestCombo;
                    strongestCombo = combo->clone();
                    delete tmp;
                }
            }
        }
        playerCombos.push_back(strongestCombo);
    }
    std::cout << "Daftar combo yang dimiliki pemain:\n";
    int i = 1;
    for (MainPlayer& p : players) {
        std::cout << "\t" << i << ". \e[1;93m" << p.getNickname() << "\e[0m: ";
        Combo& combo = *playerCombos[i - 1];
        Utils::forEach(combo.getCards(),
                       [](const MainCard& c) { std::cout << c << ", "; });
        std::cout << "\e[1;91m" << combo.getName() << "\e[0m\n";
        i++;
    }
    std::cout << "Pemilik combo terkuat adalah ";
    float max = playerCombos[0]->value();
    int winnerIdx = 0;
    for (int i = 0; i < players.size(); i++) {
        if (playerCombos[i]->value() > max) {
            max = playerCombos[i]->value();
            winnerIdx = i;
        }
    }
    MainPlayer& winner = players[winnerIdx];
    std::cout << "\e[1;93m" << winner.getNickname() << "\e[0m\n";
    winner.setPoints(winner.getPoints() + gameManager.getPot());
    cout << "Point yang dimenangkan sebesar " << gameManager.getPot() << endl;
    // clean up
    for (auto c : playerCombos) {
        delete c;
    }
    if (Utils::filter_vector<MainPlayer>(players, [](const MainPlayer& p) {
            return p.getPoints() >= (1l << 32);
        }).empty()) {
        gameManager.setupGame();
        return GameState::getState("dashboard");
    } else {
        return GameState::getState("conclusion");
    }
}

Conclusion::Conclusion(GameManager& gm) : GameState(false), gameManager(gm) {}

GameState* Conclusion::updateState()
{
    std::cout
        << "\e[1;91mPermainan berakhir.\e[0m\n\e[4;93mLeaderboard:\e[0m\n";
    std::vector<MainPlayer> players(gameManager.getPlayers());
    std::sort(players.begin(), players.end(),
              [](const MainPlayer& a, const MainPlayer& b) {
                  return a.getPoints() > b.getPoints();
              });
    int i = 1;
    for (const MainPlayer& p : players) {
        std::cout << "\t" << i++ << ". \e[1;93m" << p.getNickname()
                  << "\e[0m: " << p.getPoints() << "\n";
    }
    std::cout << "Permainan dimenangkan oleh \e[1;93m"
              << players[0].getNickname()
              << "\e[0m.\nLanjut?\n\t1. Main lagi\n\t2. Exit\n";
    int cont;
    Utils::input_validate(cont, 1, 2);
    if (cont == 1) {
        gameManager.reset();
        Ability::reset();
        return GameState::getState("player registration");
    } else {
        return GameState::getState("end");
    }
}

End::End() : GameState(true) {}
GameState* End::updateState()
{
    std::cout << "Bye.\n";
    return this;
}
