#include "../../lib/GameManager.hpp"
#include "../../lib/entities/Player.hpp"

GameManager::GameManager()
{
    currentPlayerIndex = 0;
    currentRound = 0;
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
        playedPlayers.clear();
    } else {
        playedPlayers.push_back(currentPlayerIndex);
    }
    // menentukan index player selanjutnya
    if (reversedDirection) {
        currentPlayerIndex--;
        if (currentPlayerIndex < 0) {
            currentPlayerIndex += players.size();
        }
    } else {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}

Player& GameManager::getCurrentPlayer() {
    return players[currentPlayerIndex];
}
