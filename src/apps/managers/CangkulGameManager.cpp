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
    nextTurnPlayerIndex = 0;
    if (nextRoundTurnQueue.empty()) {
        currentPlayerIndex = 0;
        nextRoundFirstPlayerIndex = 1;
    } else if (deck.getAll().empty()) {
        setupRound();
    }

    nilaiKartuTertinggi = 0;

    deck.clear();
    fillDeck();
    deck.shuffle();
    table.put(deck.takeCard());
}

void CangkulGameManager::fillDeck()
{
    for (int tipe = 0; tipe < 4; tipe++) {
        for (int number = 2; number <= 14; number++) {
            deck.putCard(Card<CardSymbol, CangkulNumber>(tipe, number));
        }
    }
}

void CangkulGameManager::registerPlayer(CangkulPlayer player)
{
    if (players.size() == 4) {
        throw "Jumlah player sudah ada 4";
    }

    for (const CangkulPlayer& p : players) {
        if (p == player) {
            throw "Player dengan nama " + player.getNickname() +
                " sudah terdaftar. Silahkan masukkan nama yang lain";
        }
    }

    for(int i = 0; i <= 6; i++){
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

int CangkulGameManager::getNextTurnPlayerIndex(){
    return nextTurnPlayerIndex;
}

int CangkulGameManager::getCurrentPlayerIndex(){
    return currentPlayerIndex;
}

void CangkulGameManager::setNextTurnPlayerIndex(int index){
    nextTurnPlayerIndex = index;
}

int CangkulGameManager::getNilaiKartuTertinggi(){
    return nilaiKartuTertinggi;
}

void CangkulGameManager::setNilaiKartuTertinggi(int nilai){
    nilaiKartuTertinggi = nilai;
}

void CangkulGameManager::nextPlayer()
{
    currentPlayerIndex++;
}

CangkulPlayer& CangkulGameManager::getCurrentPlayer()
{
    return players[currentPlayerIndex];
}

std::vector<CangkulPlayer>& CangkulGameManager::getPlayers()
{
    return players;
}

int CangkulGameManager::getCurrentRound() const
{
    return currentRound;
}
