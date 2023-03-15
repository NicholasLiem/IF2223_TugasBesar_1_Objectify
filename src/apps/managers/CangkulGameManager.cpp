#include "CangkulGameManager.hpp"

#include "Ability.hpp"
#include "Player.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

CangkulGameManager::CangkulGameManager()
{
    setupGame();
}

void CangkulGameManager::reset()
{
    nextRoundTurnQueue.clear();
    currentRoundTurnQueue.clear();
    table.clear();
    deck.clear();
    players.clear();
    setupGame();
}

void CangkulGameManager::setupGame()
{
    currentRound = 1;
    if (nextRoundTurnQueue.empty()) {
        currentPlayerIndex = 0;
        nextRoundFirstPlayerIndex = 1;
    } else if (deck.getAll().empty()) {
        setupRound();
    }


    deck.clear();
    fillDeck();
    deck.shuffle();
    table.put(deck.takeCard());
}

void CangkulGameManager::fillDeck()
{
    for (int tipe = 0; tipe < 4; tipe++) {
        for (int number = 1; number <= 13; number++) {
            deck.putCard(Card<CardSymbol, CangkulNumber>(tipe, number));
        }
    }
}

void CangkulGameManager::registerPlayer(Player<CardSymbol, CangkulNumber> player)
{
    if (players.size() == 4) {
        throw "Jumlah player sudah ada 4";
    }

    for (const Player<CardSymbol, CangkulNumber>& p : players) {
        if (p == player) {
            throw "Player dengan nama " + player.getNickname() +
                " sudah terdaftar. Silahkan masukkan nama yang lain";
        }
    }

    for(int i = 0; i <= 7; i++){
        player.put(deck.takeCard());
    }

    players.push_back(player);
    if (players.size() == 4) {
        setupRound();
    }
}

void CangkulGameManager::setupRound()
{

}

void CangkulGameManager::nextPlayer()
{
}

Player<CardSymbol, CangkulNumber>& CangkulGameManager::getCurrentPlayer()
{
    return players[currentPlayerIndex];
}

std::vector<Player<CardSymbol, CangkulNumber>>& CangkulGameManager::getPlayers()
{
    return players;
}

int CangkulGameManager::getCurrentRound() const
{
    return currentRound;
}
