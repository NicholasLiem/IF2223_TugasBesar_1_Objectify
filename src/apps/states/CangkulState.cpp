#include "CangkulState.hpp"

#include "Action.hpp"
#include "Combo.hpp"
#include "Exceptions.hpp"
#include "GameState.hpp"
#include "Utils.hpp"

#include <iostream>
#include <string>
#include <vector>

CangkulDashboard::CangkulDashboard(CangkulGameManager& gm)
    : GameState(false), gameManager(gm)
{
}

GameState* CangkulDashboard::updateState()
{
    cout << "Ronde ke-" << gameManager.getCurrentRound() << endl;
    return GameState::getState("end");
}

CangkulPlayerTurn::CangkulPlayerTurn(CangkulGameManager& game)
    : GameState(false), gameManager(game)
{
}

GameState* CangkulPlayerTurn::updateState()
{
    vector<CangkulCard>& tableCard = gameManager.table.getInventory();
    CangkulCard tableCardCurrent = tableCard[0];

    CangkulPlayer& currentPlayer = gameManager.getCurrentPlayer();
    vector<CangkulCard>& playerCard = currentPlayer.getInventory();

    cout << "Kartu di meja: " << tableCardCurrent << endl;
    currentPlayer.printInventory();

    if (!currentPlayer.hasTypeCard(tableCardCurrent)) {
        return GameState::getState("draw card");
    } else {
        cout << "Pilih kartu yang mau dikeluarkan: \n";
        int index;
        std::cout << "> ";
        std::cin >> index;
        Card<CardSymbol, CangkulNumber> card = playerCard[index-1];
        cout << "TERPILIH:" << card;
        if (card.getColor() == tableCardCurrent.getColor()){
            gameManager.table.put(currentPlayer.take(playerCard[index-1]));
            return GameState::getState("dashboard");
        } else {
            cout << "Kartu yang dipilih tidak sesuai dengan tipe kartu di meja" << endl;
            return GameState::getState("player turn");
        }
    }

    return GameState::getState("dashboard");
}

CangkulPlayerRegistration::CangkulPlayerRegistration(
    CangkulGameManager& gameManager)
    : GameState(false), gameManager(gameManager)
{
}

GameState* CangkulPlayerRegistration::updateState()
{
    std::string first;
    for (int i = 1; i <= 4;) {
        std::string name;
        std::cout << "Masukkan nickname player " << i << ": ";
        std::cin >> name;
        try {
            gameManager.registerPlayer(CangkulPlayer(name));
            std::cout << "Player " << i
                      << " \e[1;93m" + name + "\e[0m telah terdaftar!"
                      << std::endl;
        } catch (const std::string& exception) {
            std::cout << exception << "\n";
            continue;
        }
        if (i == 1) {
            first = name;
        }
        i++;
    }
    std::cout << "Giliran pertama diambil oleh \e[1;93m" << first << "\e[0m"
              << std::endl;
    return GameState::getState("player turn");
}

CangkulConclusion::CangkulConclusion(CangkulGameManager& gm)
    : GameState(false), gameManager(gm)
{
}

GameState* CangkulConclusion::updateState()
{
    cout << "aaaa";
    return GameState::getState("player turn");
}

CangkulPilihKartu::CangkulPilihKartu(CangkulGameManager& gm)
    : GameState(false), gameManager(gm)
{
}

GameState* CangkulPilihKartu::updateState()
{
    cout << "Pilih Kartu: ";
    return GameState::getState("player turn");
}

CangkulDrawCard::CangkulDrawCard(CangkulGameManager& gm)
    : GameState(false), gameManager(gm)
{
}

GameState* CangkulDrawCard::updateState()
{
    CangkulPlayer& currentPlayer = gameManager.getCurrentPlayer();
    currentPlayer.put(gameManager.deck.takeCard());
    cout << "Player " << gameManager.getCurrentPlayer().getNickname()
         << " mengambil kartu!" << endl;
    return GameState::getState("player turn");
}
