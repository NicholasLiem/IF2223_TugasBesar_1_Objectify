#include "GameManager.hpp"

#include "Ability.hpp"
#include "Player.hpp"

#include <vector>

GameManager::GameManager()
{
    currentRound = 1;
    currentPlayerIndex = 0;
    nextRoundFirstPlayerIndex = 1;
    reversedDirection = false;
    pot = 0;
}

void GameManager::registerPlayer(Player player)
{
    players.push_back(player);
}
void GameManager::reverseDirection()
{
    reversedDirection = !reversedDirection;
}

void GameManager::nextPlayer()
{
    // menentukan peralihan ronde
    if (playedPlayers.size() == players.size() - 1) {
        currentRound++;
        setupRound();
    } else {
        playedPlayers.push_back(currentPlayerIndex);
        if (reversedDirection) {
            currentPlayerIndex +=
                (--currentPlayerIndex < 0) ? players.size() : 0;
        } else {
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
        }
    }
}

void GameManager::setupRound()
{
    playedPlayers.clear();
    currentPlayerIndex = nextRoundFirstPlayerIndex;
    if (reversedDirection) {
        nextRoundFirstPlayerIndex +=
            (--nextRoundFirstPlayerIndex < 0) ? players.size() : 0;
    } else {
        nextRoundFirstPlayerIndex++; // should not reach players.size()
    }
    table.takeAll();
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

Ability* GameManager::getAbility(std::string playerNickname) {
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
