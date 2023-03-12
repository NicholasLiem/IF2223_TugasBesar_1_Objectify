#include "Next.hpp"

#include "Action.hpp"
#include "GameManager.hpp"
#include "GameState.hpp"
#include "PlayerTurn.hpp"

#include <iostream>

Next::Next(GameManager& gameManager) : Action(gameManager) {}

GameState* Next::updateState()
{
    std::cout << "Giliran dilanjut ke pemain selanjutnya\n";
    gameManager.nextPlayer();
    return GameState::getState("player turn");
}
