#include "GameManager.hpp"

#include "Ability.hpp"
#include "Player.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

GameManager::GameManager(std::string configPath)
{
    configFilePath = configPath;
    setupGame();
}

GameManager::GameManager() : GameManager("") {}

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
    if (!players.empty()) {
        Ability::reset();
        for (Player& p : players) {
            p.put(deck.takeCard());
            p.put(deck.takeCard());
        }
        table.put(deck.takeCard());
    }
}

void GameManager::fillDeck()
{
    if (configFilePath != "") {
        int line = 1;
        try {
            std::ifstream file(configFilePath);
            Card c(0, 0);
            while (line <= 52) {
                file >> c;
                for (const Card& card : deck.getAll()) {
                    if (card.getNumber() == c.getNumber() &&
                        card.getColor() == c.getColor()) {
                        throw "Configuration error: Card duplication";
                    }
                }
                deck.putCard(c);
                line++;
            }
            if (deck.getAll().size() < 52) {
                throw "Configuration error: Non-exhaustive card "
                      "configuration";
            }
        } catch (const std::ifstream::failure& e) {
            std::cout << "Error reading file: " << e.what()
                      << "\nDecided to fill the deck randomly\n";
            deck.clear();
        } catch (const char* e) {
            std::cout << e << "\nDecided to fill the deck randomly\n";
            deck.clear();
        } catch (const std::string& e) {
            std::cout << e << " at line " << std::to_string(line)
                      << "\nDecided to fill the deck randomly\n";
            deck.clear();
        }
    }
    if (deck.getAll().empty()) {
        for (int color = 0; color < 4; color++) {
            for (int number = 1; number <= 13; number++) {
                deck.putCard(Card(color, number));
            }
        }
        deck.shuffle();
    }
}

void GameManager::registerPlayer(Player player)
{
    if (players.size() == 7) {
        throw "Jumlah player sudah ada 7";
    }
    for (const Player& p : players) {
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
    for (Player& player : players) {
        Ability* ability = abilities.get(i);
        playerAbilities[player.getNickname()] = ability;
        std::cout << player.getNickname() << " mendapatkan ability "
                  << ability->getName() << std::endl;
        ability->setOwner(&player);
        i++;
    }
}

std::vector<Player>& GameManager::getPlayers()
{
    return players;
}

Player& GameManager::getCurrentPlayer()
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
