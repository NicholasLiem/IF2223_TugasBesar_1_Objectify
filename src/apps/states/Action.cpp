#include "Action.hpp"

#include "Ability.hpp"
#include "GameManager.hpp"
#include "Player.hpp"

#include <algorithm>
#include <ios>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>

bool check_ability(const Ability& ability, const std::string name)
{
    if (ability.getName() != name) {
        std::cout << "Ets, tidak bisa. Kamu tidak punya " << name << std::endl;
        return false;
    }
    if (ability.isUsed()) {
        std::cout << "Kamu sudah menggunakan ability ini sebelumnya"
                  << std::endl;
        return false;
    }
    if (ability.isMuted()) {
        std::cout << "Abiity sudah dinonaktifkan oleh pemain lain!"
                  << std::endl;
        return false;
    }
    return true;
}

template <class Type>
void input_validate(Type&& var, int lower, int upper)
{
    std::cout << "> ";
    std::string temp;
    while (!(std::cin >> var) || var < lower || var > upper) {
        std::cout << "Masukan tidak valid!\n";
        std::cout << "> ";
        std::cin.clear();
        std::getline(std::cin, temp);
    }
}

Scoreboard::Scoreboard(GameManager& gm) : Action(gm) {}

GameState* Scoreboard::updateState()
{
    std::vector<Player> players(gameManager.getPlayers());
    std::sort(players.begin(), players.end(),
              [](const Player& a, const Player& b) {
                  return a.getPoints() > b.getPoints();
              });
    int i = 1;
    std::cout << "\e[4;93mScoreboard\e[0m\n";
    for (const Player& p : players) {
        std::cout << "\t" << i++ << ". " << p.getNickname() << " ("
                  << p.getPoints() << ")\n";
    }
    return GameState::getState("dashboard");
}

Double::Double(GameManager& gameManager) : Action(gameManager) {}

GameState* Double::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    std::cout << player.getNickname() << " melakukan Double!";
    std::cout << " Poin hadiah naik dari " << gameManager.getPot();
    gameManager.setPot(gameManager.getPot() * 2);
    std::cout << " menjadi " << gameManager.getPot() << "!\n";
    gameManager.nextPlayer();
    return GameState::getState("dashboard");
}

Half::Half(GameManager& gameManager) : Action(gameManager) {}

GameState* Half::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    std::cout << player.getNickname() << " melakukan Half!";
    std::cout << " Poin hadiah turun dari " << gameManager.getPot();
    long currPot = gameManager.getPot();
    long newPot = currPot / 2 < 1 ? 1 : currPot / 2;
    gameManager.setPot(newPot);
    std::cout << " menjadi " << gameManager.getPot() << "!\n";
    gameManager.nextPlayer();
    return GameState::getState("dashboard");
}

Next::Next(GameManager& gameManager) : Action(gameManager) {}

GameState* Next::updateState()
{
    gameManager.nextPlayer();
    std::string name = gameManager.getCurrentPlayer().getNickname();
    std::cout << "Giliran dilanjut ke \e[4m" + name + "\e[0m" << std::endl;
    return GameState::getState("dashboard");
}

QuadrupleAct::QuadrupleAct(GameManager& gameManager) : Action(gameManager) {}

GameState* QuadrupleAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Quadruple Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << player.getNickname() << " melakukan Quadruple!";
    std::cout << " Poin hadiah naik dari " << gameManager.getPot();
    ability.useAbility();
    std::cout << " menjadi " << gameManager.getPot() << "!" << std::endl;
    gameManager.nextPlayer();
    return GameState::getState("dashboard");
}

QuarterAct::QuarterAct(GameManager& gameManager) : Action(gameManager) {}

GameState* QuarterAct::updateState()
{

    Player& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Quarter Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << player.getNickname() << " melakukan Quarter!";
    std::cout << " Poin hadiah turun dari " << gameManager.getPot();
    ability.useAbility();
    std::cout << " menjadi " << gameManager.getPot() << "!" << std::endl;
    gameManager.nextPlayer();
    return GameState::getState("dashboard");
}

ReRollAct::ReRollAct(GameManager& gameManager) : Action(gameManager) {}

GameState* ReRollAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "ReRoll Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << "Melakukan pembuangan kartu yang sedang dimiliki\n";
    ability.useAbility();
    std::cout << "Kamu mendapatkan 2 kartu baru yaitu:\n";
    int i = 1;
    for (auto& x : player.getAll()) {
        std::cout << "\t" << i++ << ". " << x << "\n";
    }
    std::flush(std::cout);
    gameManager.nextPlayer();
    return GameState::getState("dashboard");
}

ReverseDirAct::ReverseDirAct(GameManager& gameManager) : Action(gameManager) {}

GameState* ReverseDirAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Reverse Direction Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << player.getNickname() << " melakukan Reverse!\n";
    ability.useAbility();
    std::cout << "Sisa urutan giliran ronde ini: ";
    std::vector<Player>& players = gameManager.getPlayers();
    for (int& x : gameManager.getCurrentRoundTurnQueue()) {
        std::cout << players[x].getNickname() << " ";
    }
    std::cout << "\n";
    std::cout << "Urutan giliran ronde berikutnya: ";
    for (int& x : gameManager.getNextRoundTurnQueue()) {
        std::cout << players[x].getNickname() << " ";
    }
    std::cout << std::endl;

    return GameState::getState("dashboard");
}

SwapAct::SwapAct(GameManager& gameManager) : Action(gameManager) {}

GameState* SwapAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Swap Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << player.getNickname() << " melakukan Swap!\n";
    std::vector<Player*> players;

    int i = 1;
    std::cout << "Silahkan pilih pemain yang kartunya ingin anda tukar:\n";
    for (Player& p : gameManager.getPlayers()) {
        if (p != player) {
            players.push_back(&p);
            std::cout << "\t" << i++ << ". " << p.getNickname() << "\n";
        }
    }
    int target_idx;
    input_validate(target_idx, 1, 6);
    Player& target1 = *players[target_idx - 1];
    players.clear();
    i = 1;
    std::cout << "Silahkan pilih pemain lain yang kartunya ingin anda tukar:\n";
    for (Player& p : gameManager.getPlayers()) {
        if (p != player && p != target1) {
            players.push_back(&p);
            std::cout << "\t" << i++ << ". " << p.getNickname() << "\n";
        }
    }
    input_validate(target_idx, 1, 5);
    Player& target2 = *players[target_idx - 1];
    std::cout << "Silahkan pilih kartu kanan/kiri " << target1.getNickname()
              << ":\n\t1. Kanan\n\t2. Kiri" << std::endl;
    int t1_side;
    input_validate(t1_side, 1, 2);
    int t2_side;
    std::cout << "Silahkan pilih kartu kanan/kiri " << target2.getNickname()
              << ":\n\t1. Kanan\n\t2. Kiri" << std::endl;
    input_validate(t2_side, 1, 2);

    SwapCard& swapcard = dynamic_cast<SwapCard&>(ability);
    swapcard.useAbility(target1, target2, t1_side - 1, t2_side - 1);
    gameManager.nextPlayer();
    return GameState::getState("dashboard");
}

SwitchAct::SwitchAct(GameManager& gameManager) : Action(gameManager) {}

GameState* SwitchAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Switch Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << player.getNickname() << " melakukan Switch!\n"
              << "Kartumu sekarang adalah " << player.get(0) << " dan "
              << player.get(1)
              << "\nSilahkan pilih pemain yang kartunya ingin anda tukar:\n";
    std::vector<Player*> players;
    int i = 1;
    for (Player& p : gameManager.getPlayers()) {
        if (p != player) {
            players.push_back(&p);
            std::cout << "\t" << i++ << ". " << p.getNickname() << "\n";
        }
    }
    int target_idx;
    input_validate(target_idx, 1, 6);
    Player& target = *players[target_idx - 1];
    SwitchCard& switchcard = dynamic_cast<SwitchCard&>(ability);
    switchcard.useAbility(target);
    std::cout << "Kedua kartu " << player.getNickname()
              << " telah ditukar dengan " << target.getNickname()
              << "!\nKartumu sekarang adalah " << player.get(0) << " dan "
              << player.get(1) << std::endl;
    gameManager.nextPlayer();
    return GameState::getState("dashboard");
}

AbilitylessAct::AbilitylessAct(GameManager& gameManager) : Action(gameManager)
{
}

GameState* AbilitylessAct::updateState()
{
    Player& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Abilityless Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << player.getNickname()
              << " akan mematikan kartu ability lawan!\n"
                 "Silahkan pilih pemain yang kartunya ingin dimatikan:\n";
    bool all_used = true;
    for (const Player& p : gameManager.getPlayers()) {
        if (p != player && !gameManager.getAbility(p.getNickname())->isUsed()) {
            all_used = false;
            break;
        }
    }
    if (all_used) {
        std::cout << "Eits, ternyata semua pemain sudah memakai kartu "
                     "kemampuan. Yah kamu kena sendiri deh, kemampuanmu "
                     "menjadi abilityless. Yah, pengunaan kartu ini sia-sia"
                  << std::endl;
        ability.setUsed(true);
        gameManager.nextPlayer();
        return GameState::getState("dashboard");
    }
    std::vector<Player*> players;
    int i = 1;
    for (Player& p : gameManager.getPlayers()) {
        if (p != player) {
            players.push_back(&p);
            std::cout << "\t" << i++ << ". " << p.getNickname() << "\n";
        }
    }
    int target_idx;
    input_validate(target_idx, 1, 6);
    Player& target = *players[target_idx - 1];
    Ability& target_ability = *gameManager.getAbility(target.getNickname());
    if (target_ability.isUsed()) {
        std::cout << "Kartu ability " << target.getNickname()
                  << " telah dipakai sebelumnya. Yah, "
                     "sayang penggunaan kartu ini sia-sia"
                  << std::endl;
        ability.setUsed(true);
        gameManager.nextPlayer();
        return GameState::getState("dashboard");
    }
    AbilitylessCard& card = dynamic_cast<AbilitylessCard&>(ability);
    card.useAbility(target);
    std::cout << "Kartu ability " << target.getNickname() << " telah dimatikan."
              << std::endl;
    gameManager.nextPlayer();
    return GameState::getState("dashboard");
}
