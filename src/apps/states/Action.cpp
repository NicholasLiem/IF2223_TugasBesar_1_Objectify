#include "Action.hpp"

#include "Ability.hpp"
#include "Player.hpp"

#include <iostream>

Double::Double(GameManager& gameManager) : Action(gameManager) {}

GameState* Double::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    std::cout << player.getNickname() << " melakukan DOUBLE!";
    std::cout << " Poin hadiah naik dari " << gameManager.getPot();
    gameManager.setPot(gameManager.getPot() * 2);
    std::cout << " menjadi " << gameManager.getPot() << "!\n";
    gameManager.nextPlayer();
    return GameState::getState("player turn");
}

Half::Half(GameManager& gameManager) : Action(gameManager) {}

GameState* Half::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    std::cout << player.getNickname() << " melakukan HALF!";
    std::cout << " Poin hadiah turun dari " << gameManager.getPot();
    std::cout << " menjadi " << gameManager.getPot() << "!\n";
    gameManager.nextPlayer();
    return GameState::getState("player turn");
}

Next::Next(GameManager& gameManager) : Action(gameManager) {}

GameState* Next::updateState()
{
    gameManager.nextPlayer();
    std::string name = gameManager.getCurrentPlayer().getNickname();
    std::cout << "Giliran dilanjut ke \e[4m" + name + "\e[0m\n";
    return GameState::getState("player turn");
}

QuadrupleAct::QuadrupleAct(GameManager& gameManager) : Action(gameManager) {}

GameState* QuadrupleAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability* ability = gameManager.getAbility(player.getNickname());
    if (ability->getName() == "quadruple") {
        std::cout << player.getNickname() << " melakukan QUADRUPLE!";
        std::cout << " Poin hadiah naik dari " << gameManager.getPot();
        ability->useAbility();
        std::cout << " menjadi " << gameManager.getPot() << "!\n";
        gameManager.nextPlayer();
    } else {
        std::cout
            << "Ets, tidak bisa. Kamu tidak punya kartu Ability QUADRUPLE.\n";
    }
    return GameState::getState("player turn");
}

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
