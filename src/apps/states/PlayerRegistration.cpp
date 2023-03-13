#include "PlayerRegistration.hpp"

#include "GameManager.hpp"
#include "GameState.hpp"

#include <iostream>

PlayerRegistration::PlayerRegistration(GameManager& gameManager)
    : GameState(false), gameManager(gameManager)
{
}

GameState* PlayerRegistration::updateState()
{
    std::string first;
    for (int i = 1; i <= 7; i++) {
        std::string name;
        std::cout << "Masukkan nickname player " << i << ": ";
        std::cin >> name;
        gameManager.registerPlayer(Player(name));
        std::cout << "Player " << i
                  << " \e[4m" + name + "\e[0m telah terdaftar!\n";
        if (i == 1) {
            first = name;
        }
    }
    std::cout << "Giliran pertama diambil oleh " + first << std::endl;
    std::cin.clear();
    return GameState::getState("player turn");
}
