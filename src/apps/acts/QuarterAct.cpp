#include "../../lib/states/QuarterAct.hpp"

#include "../../lib/GameManager.hpp"
#include "../../lib/entities/Ability.hpp"
#include "../../lib/entities/Player.hpp"
#include "../../lib/states/Action.hpp"

#include <iostream>

QuarterAct::QuarterAct(GameManager& gameManager) : Action(gameManager) {}

GameState* QuarterAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    if (gameManager.getAbility(player.getNickname()).getName() == "quarter") {
        std::cout << player.getNickname() << " melakukan QUARTER!";
        std::cout << " Poin hadiah turun dari " << gameManager.getPot();
        doAction();
        std::cout << " menjadi " << gameManager.getPot() << "!\n";
        gameManager.nextPlayer();
    } else {
        std::cout
            << "Ets, tidak bisa. Kamu tidak punya kartu Ability QUARTER.\n";
    }
    return GameState::getState("player turn");
}

void QuarterAct::doAction()
{
    gameManager.setPot(gameManager.getPot() / 4);
}
