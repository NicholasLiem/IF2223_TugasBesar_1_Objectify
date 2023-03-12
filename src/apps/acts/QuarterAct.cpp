#include "QuarterAct.hpp"

#include "Ability.hpp"
#include "Action.hpp"
#include "GameManager.hpp"
#include "Player.hpp"

#include <iostream>

QuarterAct::QuarterAct(GameManager& gameManager) : Action(gameManager) {}

GameState* QuarterAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability* ability = gameManager.getAbility(player.getNickname());
    if (ability->getName() == "quarter") {
        std::cout << player.getNickname() << " melakukan QUARTER!";
        std::cout << " Poin hadiah turun dari " << gameManager.getPot();
        ability->useAbility();
        std::cout << " menjadi " << gameManager.getPot() << "!\n";
        gameManager.nextPlayer();
    } else {
        std::cout
            << "Ets, tidak bisa. Kamu tidak punya kartu Ability QUARTER.\n";
    }
    return GameState::getState("player turn");
}
