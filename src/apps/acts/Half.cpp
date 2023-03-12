#include "../../lib/states/Half.hpp"

#include "../../lib/GameManager.hpp"
#include "../../lib/entities/Player.hpp"
#include "../../lib/states/Action.hpp"

#include <iostream>

Half::Half(GameManager& gameManager) : Action(gameManager) {}

GameState* Half::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    std::cout << player.getNickname() << " melakukan HALF!";
    std::cout << " Poin hadiah turun dari " << gameManager.getPot();
    doAction();
    std::cout << " menjadi " << gameManager.getPot() << "!\n";
    gameManager.nextPlayer();
    return GameState::getState("player turn");
}

void Half::doAction()
{
    gameManager.setPot(gameManager.getPot() / 2);
}
