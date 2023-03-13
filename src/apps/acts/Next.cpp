#include "Next.hpp"

#include "Action.hpp"
#include "GameManager.hpp"
#include "GameState.hpp"
#include "PlayerTurn.hpp"

#include <iostream>

Next::Next(GameManager& gameManager) : Action(gameManager) {}

GameState* Next::updateState()
{
    gameManager.nextPlayer();
    std::string name = gameManager.getCurrentPlayer().getNickname();
    std::cout << "Giliran dilanjut ke \e[4m" + name + "\e[0m\n";
    return GameState::getState("player turn");
}
