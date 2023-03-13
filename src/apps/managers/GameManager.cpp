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
    pot = 0;
    fillDeck();
    setupRound();
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
    players.push_back(player);
    player.put(deck.takeCard());
    player.put(deck.takeCard());
}

void GameManager::reverseDirection()
{
    std::reverse(currentRoundTurnQueue.begin(), currentRoundTurnQueue.end());
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
    nextRoundFirstPlayerIndex = nextRoundTurnQueue[0];
    nextRoundTurnQueue.clear();
    for (int i = nextRoundFirstPlayerIndex;
         currentRoundTurnQueue.size() != players.size() - 1;) {
        currentRoundTurnQueue.push_back(i);
        nextRoundTurnQueue.push_back(i);
        if (reversedDirection) {
            i += (--i < 0) ? players.size() : 0;
        } else {
            i = (i + 1) % players.size();
        }
    }
    nextRoundTurnQueue.push_back(currentPlayerIndex);
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
        playerAbilities[player.getNickname()] = abilities.get(i);
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
