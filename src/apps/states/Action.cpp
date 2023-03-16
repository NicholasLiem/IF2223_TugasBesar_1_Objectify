#include "Action.hpp"

#include "Ability.hpp"
#include "GameManager.hpp"
#include "Player.hpp"
#include "Utils.hpp"

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

Scoreboard::Scoreboard(GameManager& gm) : Action(gm) {}

GameState* Scoreboard::updateState()
{
    std::vector<MainPlayer> players(gameManager.getPlayers());
    int i = 1;
    std::cout
        << "\e[0;36m==========[\e[1;36m Scoreboard \e[0;36m]=========\e[0m\n";
    for (const MainPlayer& p : players) {
        std::cout << "\t" << i++ << ". \e[1;93m" << p.getNickname()
                  << "\e[0m: " << p.getPoints() << "\n";
    }
    return GameState::getState("dashboard");
}

Double::Double(GameManager& gameManager) : Action(gameManager) {}

GameState* Double::updateState()
{
    MainPlayer& player = gameManager.getCurrentPlayer();
    std::cout << "\e[1;93m" << player.getNickname()
              << "\e[0m melakukan Double!";
    std::cout << " Poin hadiah naik dari " << gameManager.getPot();
    gameManager.setPot(gameManager.getPot() * 2);
    std::cout << " menjadi " << gameManager.getPot() << "!\n";
    return GameState::getState("next");
}

Half::Half(GameManager& gameManager) : Action(gameManager) {}

GameState* Half::updateState()
{
    MainPlayer& player = gameManager.getCurrentPlayer();
    std::cout << "\e[1;93m" << player.getNickname() << "\e[0m melakukan Half!";
    long currPot = gameManager.getPot();
    if (currPot == 1) {
        std::cout << " Sayangnya poin hadiah sudah bernilai 1. Poin hadiah "
                     "tidak berubah..\n";
    } else {
        std::cout << " Poin hadiah turun dari " << currPot;
        gameManager.setPot(currPot / 2);
        std::cout << " menjadi " << gameManager.getPot() << "!\n";
    }
    return GameState::getState("next");
}

Next::Next(GameManager& gameManager) : Action(gameManager) {}

GameState* Next::updateState()
{
    gameManager.nextPlayer();
    std::string name = gameManager.getCurrentPlayer().getNickname();
    std::cout << "Giliran dilanjut ke \e[1;93m" + name + "\e[0m" << std::endl;
    return GameState::getState("dashboard");
}

QuadrupleAct::QuadrupleAct(GameManager& gameManager) : Action(gameManager) {}

GameState* QuadrupleAct::updateState()
{
    MainPlayer& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Quadruple Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << "\e[1;93m" << player.getNickname()
              << "\e[0m melakukan Quadruple!";
    std::cout << " Poin hadiah naik dari " << gameManager.getPot();
    ability.useAbility();
    std::cout << " menjadi " << gameManager.getPot() << "!" << std::endl;
    return GameState::getState("next");
}

QuarterAct::QuarterAct(GameManager& gameManager) : Action(gameManager) {}

GameState* QuarterAct::updateState()
{

    MainPlayer& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Quarter Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << "\e[1;93m" << player.getNickname()
              << "\e[0m melakukan Quarter!";
    if (gameManager.getPot() == 1) {
        std::cout
            << " Sayangnya poin hadiah sudah bernilai 1. Poin hadiah tidak "
               "berubah.. Yah, sayang penggunaan kartu ini sia-sia!\n";
        ability.useAbility();
    } else {
        std::cout << " Poin hadiah turun dari " << gameManager.getPot();
        ability.useAbility();
        std::cout << " menjadi " << gameManager.getPot() << "!" << std::endl;
    }
    return GameState::getState("next");
}

ReRollAct::ReRollAct(GameManager& gameManager) : Action(gameManager) {}

GameState* ReRollAct::updateState()
{
    MainPlayer& player = gameManager.getCurrentPlayer();
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
    return GameState::getState("next");
}

ReverseDirAct::ReverseDirAct(GameManager& gameManager) : Action(gameManager) {}

GameState* ReverseDirAct::updateState()
{
    MainPlayer& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Reverse Direction Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << "\e[1;93m" << player.getNickname()
              << "\e[0m melakukan Reverse!\n";
    ability.useAbility();
    std::cout << "Sisa urutan giliran ronde ini: ";
    std::vector<MainPlayer>& players = gameManager.getPlayers();
    std::cout << "\e[1;93m";
    for (int& x : gameManager.getCurrentRoundTurnQueue()) {
        std::cout << players[x].getNickname() << " ";
    }
    std::cout << "\e[0m\nUrutan giliran ronde berikutnya: \e[1;93m";
    for (int& x : gameManager.getNextRoundTurnQueue()) {
        std::cout << players[x].getNickname() << " ";
    }
    std::cout << "\e[0m" << std::endl;

    return GameState::getState("dashboard");
}

SwapAct::SwapAct(GameManager& gameManager) : Action(gameManager) {}

GameState* SwapAct::updateState()
{
    MainPlayer& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Swap Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << "\e[1;93m " << player.getNickname()
              << "\e[0m melakukan Swap!\n";
    std::vector<MainPlayer*> players;

    int i = 1;
    std::cout << "Silahkan pilih pemain yang kartunya ingin anda tukar:\n";
    for (MainPlayer& p : gameManager.getPlayers()) {
        if (p != player) {
            players.push_back(&p);
            std::cout << "\t" << i++ << ". \e[1;93m" << p.getNickname()
                      << "\e[0m\n";
        }
    }
    int target_idx;
    Utils::input_validate(target_idx, 1, 6);
    MainPlayer& target1 = *players[target_idx - 1];
    players.clear();
    i = 1;
    std::cout << "Silahkan pilih pemain lain yang kartunya ingin anda tukar:\n";
    for (MainPlayer& p : gameManager.getPlayers()) {
        if (p != player && p != target1) {
            players.push_back(&p);
            std::cout << "\t" << i++ << ". \e[1;93m" << p.getNickname()
                      << "\e[0m\n";
        }
    }
    Utils::input_validate(target_idx, 1, 5);
    MainPlayer& target2 = *players[target_idx - 1];
    std::cout << "Silahkan pilih kartu kanan/kiri \e[1;93m"
              << target1.getNickname() << "\e[0m:\n\t1. Kanan\n\t2. Kiri"
              << std::endl;
    int t1_side;
    Utils::input_validate(t1_side, 1, 2);
    int t2_side;
    std::cout << "Silahkan pilih kartu kanan/kiri \e[1;93m"
              << target2.getNickname() << "\e[0m:\n\t1. Kanan\n\t2. Kiri"
              << std::endl;
    Utils::input_validate(t2_side, 1, 2);

    SwapCard& swapcard = dynamic_cast<SwapCard&>(ability);
    swapcard.useAbility(target1, target2, t1_side - 1, t2_side - 1);
    return GameState::getState("next");
}

SwitchAct::SwitchAct(GameManager& gameManager) : Action(gameManager) {}

GameState* SwitchAct::updateState()
{
    MainPlayer& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Switch Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << "\e[1;93m" << player.getNickname()
              << "\e[0m melakukan Switch!\n"
              << "Kartumu sekarang adalah " << player.get(0) << " dan "
              << player.get(1)
              << "\nSilahkan pilih pemain yang kartunya ingin anda tukar:\n";
    std::vector<MainPlayer*> players;
    int i = 1;
    for (MainPlayer& p : gameManager.getPlayers()) {
        if (p != player) {
            players.push_back(&p);
            std::cout << "\t" << i++ << ". \e[1;93m" << p.getNickname()
                      << "\e[0m\n";
        }
    }
    int target_idx;
    Utils::input_validate(target_idx, 1, 6);
    MainPlayer& target = *players[target_idx - 1];
    SwitchCard& switchcard = dynamic_cast<SwitchCard&>(ability);
    switchcard.useAbility(target);
    std::cout << "Kedua kartu \e[1;93m" << player.getNickname()
              << "\e[0m telah ditukar dengan \e[1;93m" << target.getNickname()
              << "\e[0m!\nKartumu sekarang adalah " << player.get(0) << " dan "
              << player.get(1) << std::endl;
    return GameState::getState("next");
}

AbilitylessAct::AbilitylessAct(GameManager& gameManager) : Action(gameManager)
{
}

GameState* AbilitylessAct::updateState()
{
    MainPlayer& player = gameManager.getCurrentPlayer();
    Ability& ability = *gameManager.getAbility(player.getNickname());
    if (!check_ability(ability, "Abilityless Card")) {
        return GameState::getState("dashboard");
    }
    std::cout << "\e[1;93m" << player.getNickname()
              << "\e[0m akan mematikan kartu ability lawan!\n"
                 "Silahkan pilih pemain yang kartunya ingin dimatikan:\n";
    bool all_used = true;
    for (const MainPlayer& p : gameManager.getPlayers()) {
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
        return GameState::getState("next");
    }
    std::vector<MainPlayer*> players;
    int i = 1;
    for (MainPlayer& p : gameManager.getPlayers()) {
        if (p != player) {
            players.push_back(&p);
            std::cout << "\t" << i++ << ". \e[1;93m" << p.getNickname()
                      << "\e[0m\n";
        }
    }
    int target_idx;
    Utils::input_validate(target_idx, 1, 6);
    MainPlayer& target = *players[target_idx - 1];
    Ability& target_ability = *gameManager.getAbility(target.getNickname());
    if (target_ability.isUsed()) {
        std::cout << "Kartu ability \e[1;93m" << target.getNickname()
                  << "\e[0m telah dipakai sebelumnya. Yah, "
                     "sayang penggunaan kartu ini sia-sia"
                  << std::endl;
        ability.setUsed(true);
        return GameState::getState("next");
    }
    AbilitylessCard& card = dynamic_cast<AbilitylessCard&>(ability);
    card.useAbility(target);
    std::cout << "Kartu ability \e[1;93m" << target.getNickname()
              << "\e[0m telah dimatikan." << std::endl;
    return GameState::getState("next");
}

HelpCommand::HelpCommand(GameManager& gm) : Action(gameManager) {}

GameState* HelpCommand::updateState()
{
    Utils::clear_screen();
    std::cout << "\e[1;93mDaftar perintah:\e[0m\n";
    std::cout << "\t1. \e[1;93mhelp\e[0m: menampilkan daftar perintah\n";
    // Isi di sini
    std::cout << std::endl;
    std::cout << "Lakukan perintah: " << std::endl;
    return GameState::getState("player turn");
}

