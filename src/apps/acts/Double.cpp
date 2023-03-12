#include "Double.hpp"

#include "Action.hpp"
#include "GameManager.hpp"
#include "Player.hpp"

#include <iostream>

Double::Double(GameManager& gameManager) : Action(gameManager) {}

GameState* Double::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    std::cout << player.getNickname() << " melakukan DOUBLE!";
    std::cout << " Poin hadiah naik dari " << gameManager.getPot();
    doAction();
    std::cout << " menjadi " << gameManager.getPot() << "!\n";
    gameManager.nextPlayer();
    return GameState::getState("player turn");
}

void Double::doAction()
{
    gameManager.setPot(gameManager.getPot() * 2);
}
