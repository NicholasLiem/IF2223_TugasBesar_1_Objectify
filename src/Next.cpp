#include "lib/states/Next.hpp"

#include "lib/GameManager.hpp"
#include "lib/GameState.hpp"
#include "lib/states/Action.hpp"
#include "lib/states/PlayerTurn.hpp"

#include <iostream>

Next::Next(GameManager& gameManager) : Action(gameManager) {}

GameState* Next::updateState()
{
    std::cout << "Giliran dilanjut ke pemain selanjutnya\n";
    gameManager.nextPlayer();
    return GameState::getState("player turn");
}

void Next::doAction() {}
