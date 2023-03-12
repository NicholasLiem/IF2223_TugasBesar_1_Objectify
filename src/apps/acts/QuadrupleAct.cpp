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
    Ability& ability = gameManager.getAbility(player.getNickname());
    if (ability.getName() == "quadruple") {
        std::cout << player.getNickname() << " melakukan QUADRUPLE!";
        std::cout << " Poin hadiah naik dari " << gameManager.getPot();
        ability.useAbility();
        std::cout << " menjadi " << gameManager.getPot() << "!\n";
        gameManager.nextPlayer();
    } else {
        std::cout
            << "Ets, tidak bisa. Kamu tidak punya kartu Ability QUADRUPLE.\n";
    }
    return GameState::getState("player turn");
}

void QuadrupleAct::doAction() {}
