#include "Action.hpp"

#include "Ability.hpp"
#include "GameManager.hpp"
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
    if (ability->getName() == "Quadruple Card") {
        if (ability->isUsed()) {
            std::cout << "Kamu sudah menggunakan ability ini sebelumnya\n";
            return GameState::getState("player turn");
        }
        if (ability->isMuted()) {
            std::cout << "Abiity sudah dinonaktifkan oleh pemain lain!\n";
            return GameState::getState("player turn");
        }
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
    if (ability->getName() == "Quarter Card") {
        if (ability->isUsed()) {
            std::cout << "Kamu sudah menggunakan ability ini sebelumnya\n";
            return GameState::getState("player turn");
        }
        if (ability->isMuted()) {
            std::cout << "Abiity sudah dinonaktifkan oleh pemain lain!\n";
            return GameState::getState("player turn");
        }
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

ReRollAct::ReRollAct(GameManager& gameManager) : Action(gameManager) {}

GameState* ReRollAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability* ability = gameManager.getAbility(player.getNickname());
    if (ability->getName() == "ReRoll Card") {
        if (ability->isUsed()) {
            std::cout << "Kamu sudah menggunakan ability ini sebelumnya\n";
            return GameState::getState("player turn");
        }
        if (ability->isMuted()) {
            std::cout << "Abiity sudah dinonaktifkan oleh pemain lain!\n";
            return GameState::getState("player turn");
        }
        std::cout << "Melakukan pembuangan kartu yang sedang dimiliki\n";
        ability->useAbility();
        std::cout << "Kamu mendapatkan 2 kartu baru yaitu:\n";
        int i = 1;
        for (auto& x : player.getAll()) {
            std::cout << "\t" << i++ << ". " << x << "\n";
        }
        gameManager.nextPlayer();
    } else {
        std::cout
            << "Ets, tidak bisa. Kamu tidak punya kartu Ability Re-Roll.\n";
    }
    return GameState::getState("player turn");
}

ReverseDirAct::ReverseDirAct(GameManager& gameManager)
    : Action(gameManager)
{
}

GameState* ReverseDirAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability* ability = gameManager.getAbility(player.getNickname());
    if (ability->getName() == "Reverse Direction Card") {
        if (ability->isUsed()) {
            std::cout << "Kamu sudah menggunakan ability ini sebelumnya\n";
            return GameState::getState("player turn");
        }
        if (ability->isMuted()) {
            std::cout << "Abiity sudah dinonaktifkan oleh pemain lain!\n";
            return GameState::getState("player turn");
        }
        std::cout << player.getNickname() << "melakukan reverse!\n";
        ability->useAbility();
        std::cout << "Sisa urutan giliran ronde ini:  ";
        for (int& x : gameManager.getCurrentRoundTurnQueue()) {
            std::cout << x << " ";
        }
        std::cout << "\n";
        std::cout << "Urutan giliran ronde berikutnya: ";
        for (int& x : gameManager.getNextRoundTurnQueue()) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    } else {
        std::cout
            << "Ets, tidak bisa. Kamu tidak punya kartu Ability QUARTER.\n";
    }
    return GameState::getState("player turn");
}
