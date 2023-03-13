#include "GameManager.hpp"

#include "Ability.hpp"
#include "Player.hpp"

#include <algorithm>
#include <vector>

GameManager::GameManager()
{
    currentRound = 1;
    currentPlayerIndex = 0;
    nextRoundFirstPlayerIndex = 1;
    reversedDirection = false;
    pot = 64;
    fillDeck();
}

GameManager::~GameManager()
{
    for (auto p : playerAbilities) {
        delete p.second;
    }
}

void GameManager::fillDeck()
{
    for (int color = 1; color <= 4; color++) {
        for (int number = 1; number <= 13; number++) {
            deck.putCard(Card(color, number));
        }
    }
}

void GameManager::registerPlayer(Player player)
{
    if (players.size() == 7) {
        throw "Jumlah player sudah ada 7";
    }
    players.push_back(player);
    player.put(deck.takeCard());
    player.put(deck.takeCard());
    if (players.size() == 7) {
        setupRound();
    }
}

void GameManager::reverseDirection()
{
    std::reverse(currentRoundTurnQueue.begin(), currentRoundTurnQueue.end());
    std::reverse(nextRoundTurnQueue.begin() + 1, nextRoundTurnQueue.end());
    reversedDirection = !reversedDirection;
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
        nextRoundTurnQueue = std::vector<int>(nextRoundTurnQueue.begin() + 1, nextRoundTurnQueue.end());
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
    for (Player& player : players) {
        Ability* ability = abilities.get(i);
        playerAbilities[player.getNickname()] = ability;
        ability->setOwner(&player);
        i++;
    }
}

Player& GameManager::getCurrentPlayer()
{
    return players[currentPlayerIndex];
}

Ability* GameManager::getAbility(std::string playerNickname)
{
    return playerAbilities[playerNickname];
}

void GameManager::setPot(int value)
{
    pot = value;
}

int GameManager::getPot() const
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
