#include "State.hpp"

#include "Ability.hpp"
#include "Action.hpp"
#include "Exceptions.hpp"

#include <cctype>
#include <iostream>
#include <string>

std::string to_lower(std::string s)
{
    std::string result;
    for (auto it = s.begin(); it != s.end(); it++) {
        result.push_back(std::tolower(*it));
    }
    return result;
}

Dashboard::Dashboard(GameManager& gm) : GameState(false), gameManager(gm) {}

GameState* Dashboard::updateState()
{
    std::cout << "\e[1;93mRonde ke-" << gameManager.getCurrentRound()
              << "\e[0m\nPoin hadiah: " << gameManager.getPot()
              << "\nKartu di meja:\n";
    int i = 1;
    for (const Card& c : gameManager.table.getAll()) {
        std::cout << "\t" << i++ << ". " << c << "\n";
    }
    const Player& player = gameManager.getCurrentPlayer();
    std::cout << "Nama pemain: " << player.getNickname()
              << "\nKartu di tangan:\n\t1. " << player.get(0) << "\n\t2. "
              << player.get(1) << "\n";
    if (gameManager.getAbility(player.getNickname()) != NULL) {
        Ability& ability = *gameManager.getAbility(player.getNickname());
        std::cout << "Kamu punya \e[4m" << ability.getName() << "\e[0m"
                  << std::endl;
    }
    return GameState::getState("player turn");
}

PlayerTurn::PlayerTurn(GameManager& game) : GameState(false), gameManager(game) {}

GameState* PlayerTurn::updateState()
{
    std::string command;
    std::cout << "> ";
    std::getline(std::cin >> std::ws, command);

    try {
        try {
            GameState* nextState = GameState::getState(to_lower(command));
            int round = gameManager.getCurrentRound();
            if (round == 1){
                if (nextState == GameState::getState("re-roll")
                    || nextState == GameState::getState("quadruple")
                    || nextState == GameState::getState("quarter")
                    || nextState == GameState::getState("reverse")
                    || nextState == GameState::getState("swapcard")
                    || nextState == GameState::getState("switch")
                    || nextState == GameState::getState("abilityless")){
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
        }
    } catch (InvalidActionException& e) {
        std::cout << e.what() << "\n";
        return GameState::getState("player turn");
    } catch (AccessAbilityException& e) {
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
            gameManager.registerPlayer(Player(name));
            std::cout << "Player " << i
                      << " \e[4m" + name + "\e[0m telah terdaftar!"
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
    std::cout << "Giliran pertama diambil oleh " << first << std::endl;
    return GameState::getState("dashboard");
}
