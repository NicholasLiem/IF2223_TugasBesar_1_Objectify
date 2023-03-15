#include "GameManager.hpp"

#include "Ability.hpp"
#include "Player.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

GameManager::GameManager()
{
    setupGame();
}

void GameManager::reset()
{
    nextRoundTurnQueue.clear();
    currentRoundTurnQueue.clear();
    playerAbilities.clear();
    table.clear();
    deck.clear();
    players.clear();
    setupGame();
}

void GameManager::setupGame()
{
    currentRound = 1;
    if (nextRoundTurnQueue.empty()) {
        currentPlayerIndex = 0;
        nextRoundFirstPlayerIndex = 1;
    } else if (deck.getAll().empty()) {
        setupRound();
    }
    table.clear();
    playerAbilities.clear();
    deck.clear();
    pot = 64;
    fillDeck();
    deck.shuffle();
    if (!players.empty()) {
        Ability::reset();
        for (Player<CardColor,CardNumber>& p : players) {
            p.put(deck.takeCard());
            p.put(deck.takeCard());
        }
        table.put(deck.takeCard());
    }
}

void GameManager::fillDeck()
{
    for (int color = 0; color < 4; color++) {
        for (int number = 1; number <= 13; number++) {
            deck.putCard(Card<CardColor,CardNumber>(color, number));
        }
    }
}

void GameManager::registerPlayer(Player<CardColor,CardNumber> player)
{
    if (players.size() == 7) {
        throw "Jumlah player sudah ada 7";
    }
    for (const Player<CardColor,CardNumber>& p : players) {
        if (p == player) {
            throw "Player dengan nama " + player.getNickname() +
                " sudah terdaftar. Silahkan masukkan nama yang lain";
        }
    }
    player.put(deck.takeCard());
    player.put(deck.takeCard());
    players.push_back(player);
    if (players.size() == 7) {
        setupRound();
    }
}

void GameManager::reverseDirection()
{
    std::reverse(currentRoundTurnQueue.begin(), currentRoundTurnQueue.end());
    std::reverse(nextRoundTurnQueue.begin() + 1, nextRoundTurnQueue.end());
}

void GameManager::nextPlayer()
{
    // menentukan peralihan ronde
    if (currentRoundTurnQueue.empty()) {
        currentRound++;
        setupRound();
    } else {
        currentPlayerIndex = currentRoundTurnQueue[0];
        currentRoundTurnQueue = std::vector<int>(
            currentRoundTurnQueue.begin() + 1, currentRoundTurnQueue.end());
    }
}

void GameManager::setupRound()
{
    if (!nextRoundTurnQueue.empty()) {
        currentPlayerIndex = nextRoundTurnQueue[0];
        nextRoundTurnQueue = std::vector<int>(nextRoundTurnQueue.begin() + 1,
                                              nextRoundTurnQueue.end());
        currentRoundTurnQueue = std::vector<int>(nextRoundTurnQueue);
        nextRoundTurnQueue.push_back(currentPlayerIndex);
    } else {
        // ronde pertama
        for (int i = 1; i < 7; i++) {
            currentRoundTurnQueue.push_back(i);
            nextRoundTurnQueue.push_back(i);
        }
        nextRoundTurnQueue.push_back(0);
    }
    if (currentRound < 6) {
        table.put(deck.takeCard());
    }
    if (currentRound == 2) {
        distributeAbilities();
    }
}

void GameManager::distributeAbilities()
{
    Deck<Ability*>& abilities = Ability::getAbilities();
    abilities.shuffle();
    int i = 0;
    for (Player<CardColor,CardNumber>& player : players) {
        Ability* ability = abilities.get(i);
        playerAbilities[player.getNickname()] = ability;
        std::cout << player.getNickname() << " mendapatkan ability "
            << ability->getName() << std::endl;
        ability->setOwner(&player);
        i++;
    }
}

std::vector<Player<CardColor,CardNumber>>& GameManager::getPlayers()
{
    return players;
}

Player<CardColor,CardNumber>& GameManager::getCurrentPlayer()
{
    return players[currentPlayerIndex];
}

Ability* GameManager::getAbility(std::string playerNickname)
{
    return playerAbilities[playerNickname];
}

void GameManager::setPot(long value)
{
    pot = value;
}

long GameManager::getPot() const
{
    return pot;
}

int GameManager::getCurrentRound() const
{
    return currentRound;
}

std::vector<int>& GameManager::getCurrentRoundTurnQueue()
{
    return currentRoundTurnQueue;
}

std::vector<int>& GameManager::getNextRoundTurnQueue()
{
    return nextRoundTurnQueue;
}
