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
    vector<CangkulCard>& tableCard = gameManager.table.getInventory();
    CangkulCard tableCardCurrent = tableCard[0];

    CangkulPlayer& currentPlayer = gameManager.getCurrentPlayer();
    vector<CangkulCard>& playerCard = currentPlayer.getInventory();
    Utils::clear_screen();
    cout << "\e[0;36m==========[ \e[1;36mDashboard\e[0m \e[0;36m]==========\e[0m" << endl;
    cout << "> Kartu di meja: \e[1;93m" << tableCardCurrent << "\e[0m" << endl;
    cout << "> Tipe Kartu Sekarang: \e[1;93m" << tableCardCurrent.getColor() << "\e[0m" << endl;
    cout << "> Nilai Kartu Tertinggi: \e[1;93m" << gameManager.getNilaiKartuTertinggi() << "\e[0m" << endl;
    cout << "> Giliran: \e[1;93m" << gameManager.getCurrentPlayer().getNickname() << "\e[0m" << endl;
    cout << "\e[0;36m=================================\e[0m" << endl;
    return GameState::getState("player turn");
}

CangkulPlayerTurn::CangkulPlayerTurn(CangkulGameManager& game)
    : GameState(false), gameManager(game){}

GameState* CangkulPlayerTurn::updateState()
{
    vector<CangkulCard>& tableCard = gameManager.table.getInventory();
    CangkulCard tableCardCurrent = tableCard[0];

    CangkulPlayer& currentPlayer = gameManager.getCurrentPlayer();
    vector<CangkulCard>& playerCard = currentPlayer.getInventory();

    cout << "> Daftar Kartu " << "\e[1;93m("  << currentPlayer.getNickname() << ")\e[0m" << ": \n";
    currentPlayer.printInventory();

    return GameState::getState("pilih kartu");
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
    return GameState::getState("dashboard");
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
    vector<CangkulCard>& tableCard = gameManager.table.getInventory();
    CangkulCard tableCardCurrent = tableCard[0];

    CangkulPlayer& currentPlayer = gameManager.getCurrentPlayer();
    vector<CangkulCard>& playerCard = currentPlayer.getInventory();

    if (!currentPlayer.hasTypeCard(tableCardCurrent)) {
        return GameState::getState("draw card");
    } else {
        cout << "Pilih kartu yang mau dikeluarkan: \n";
        int index;
        std::cout << "> ";
        std::cin >> index;
        CangkulCard card = playerCard[index-1];
        if (card.getColor() == tableCardCurrent.getColor()){
            if (int (card.getNumber()) > gameManager.getNilaiKartuTertinggi()){
                gameManager.setNilaiKartuTertinggi(int (card.getNumber()));
                gameManager.setNextTurnPlayerIndex(gameManager.getCurrentPlayerIndex());
            }
            cout << "Kartu yang dikeluaran adalah : " << card << endl;
            gameManager.table.put(currentPlayer.take(card));
        } else {
            cout << "Kartu yang dipilih tidak sesuai dengan tipe kartu di meja!" << endl;
        }
    }
    return GameState::getState("next turn");
}

CangkulDrawCard::CangkulDrawCard(CangkulGameManager& gm)
    : GameState(false), gameManager(gm)
{
}

GameState* CangkulDrawCard::updateState()
{
    vector<CangkulCard>& tableCard = gameManager.table.getInventory();
    CangkulCard tableCardCurrent = tableCard[0];

    CangkulPlayer& currentPlayer = gameManager.getCurrentPlayer();
    vector<CangkulCard>& playerCard = currentPlayer.getInventory();

    while(!currentPlayer.hasTypeCard(tableCardCurrent)){
        currentPlayer.put(gameManager.deck.takeCard());
        // cout << "Player " << gameManager.getCurrentPlayer().getNickname()
        //      << " mengambil kartu!" << endl;
    }
    return GameState::getState("dashboard");
}

CangkulNextPlayer::CangkulNextPlayer(CangkulGameManager& gm) : GameState(false), gameManager(gm){}

GameState* CangkulNextPlayer::updateState(){
    gameManager.nextPlayer();
    std::string name = gameManager.getCurrentPlayer().getNickname();
    std::cout << "Giliran dilanjut ke \e[1;93m" + name + "\e[0m" << std::endl;
    return GameState::getState("dashboard");
}
