#include "lib/states/PlayerTurn.hpp"

#include "lib/Exceptions.hpp"
#include "lib/states/Action.hpp"

#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>

std::string to_lower(std::string s)
{
    std::string result;
    for (auto it = s.begin(); it != s.end(); it++) {
        result.push_back(std::tolower(*it));
    }
    return result;
}

PlayerTurn::PlayerTurn() : GameState(false) {}

GameState* PlayerTurn::updateState()
{
    std::string command;

    std::cout << "> ";
    std::getline(std::cin, command);

    try {
        try {
            // input nama state yang lain tidak diizinkan
            GameState* nextState = GameState::getState(to_lower(command));
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
    }
}
