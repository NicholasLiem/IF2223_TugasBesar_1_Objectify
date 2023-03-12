#include "QuadrupleAct.hpp"

#include "Ability.hpp"
#include "Action.hpp"
#include "GameManager.hpp"
#include "Player.hpp"

#include <iostream>

QuadrupleAct::QuadrupleAct(GameManager& gameManager) : Action(gameManager) {}

GameState* QuadrupleAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    if (gameManager.getAbility(player.getNickname()).getName() == "quadruple") {
        std::cout << player.getNickname() << " melakukan QUADRUPLE!";
        std::cout << " Poin hadiah naik dari " << gameManager.getPot();
        doAction();
        std::cout << " menjadi " << gameManager.getPot() << "!\n";
        gameManager.nextPlayer();
    } else {
        std::cout
            << "Ets, tidak bisa. Kamu tidak punya kartu Ability QUADRUPLE.\n";
    }
    return GameState::getState("player turn");
}

void QuadrupleAct::doAction()
{
    gameManager.setPot(gameManager.getPot() * 4);
}
