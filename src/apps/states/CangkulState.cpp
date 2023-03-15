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
    cout
        << "\e[0;36m==========[ \e[1;36mDashboard\e[0m \e[0;36m]==========\e[0m"
        << endl;
    cout << "> Kartu di meja: \e[1;93m" << tableCardCurrent << "\e[0m" << endl;
    cout << "> Tipe Kartu Sekarang: \e[1;93m" << tableCardCurrent.getColor()
         << "\e[0m" << endl;
    cout << "> Nilai Kartu Tertinggi: \e[1;93m"
         << gameManager.getNilaiKartuTertinggi() << "\e[0m" << endl;
    cout << "> Pemegang Nilai Kartu Tertinggi: \e[1;94m"
         << gameManager.getPlayers()[gameManager.getNextTurnPlayerIndex()]
                .getNickname()
         << "\e[0m" << endl;
    cout << "> Giliran: \e[1;93m"
         << gameManager.getCurrentPlayer().getNickname() << "\e[0m" << endl;
    cout << "> Jumlah Kartu Tiap Pemain:" << endl;
    for (int i = 0; i < gameManager.getPlayers().size(); i++) {
        cout << "\t\e[1;95m" << gameManager.getPlayers()[i].getNickname()
             << "\e[0m: " << gameManager.getPlayers()[i].getInventory().size()
             << endl;
    }
    cout << "> Jumlah Kartu Di Deck:" << endl;
    cout << "\t\e[1;95m"
         << "Count"
         << "\e[0m: " << gameManager.deck.getInventory().size() << endl;
    cout << "> Jumlah Kartu Di Meja:" << endl;
    cout << "\t\e[1;95m"
         << "Count"
         << "\e[0m: " << gameManager.table.getInventory().size() << endl;
    cout << "\e[0;36m=================================\e[0m" << endl;
    return GameState::getState("player turn");
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

    cout << "> Daftar Kartu "
         << "\e[1;93m(" << currentPlayer.getNickname() << ")\e[0m"
         << ": \n";
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
    Utils::clear_screen();
    for (int i = 1; i <= 4;) {
        std::string name;
        std::cout << std::endl;
        std::cout << "Masukkan nickname player " << i << ": ";
        std::cin >> name;
        std::cout << std::endl;
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
    Utils::clear_screen();
    cout << endl;
    cout << "Selamat kepada \e[1;93m" << gameManager.getWinner().getNickname()
         << "\e[0m"
         << " yang telah memenangkan permainan ini!" << endl;
    cout << endl;
    return GameState::getState("end");
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

    for (CangkulPlayer p : gameManager.getPlayers()) {
        if (p.getInventory().size() == 0) {
            gameManager.setWinner(p);
            return GameState::getState("conclusion");
        }
    }

    if (!currentPlayer.hasTypeCard(tableCardCurrent)) {
        return GameState::getState("draw card");
    } else {
        cout << endl;
        cout << "Pilih kartu yang mau dikeluarkan: \n";
        int index;
        Utils::input_validate(index, 1, playerCard.size());
        try {
            CangkulCard card = playerCard[index - 1];
            if (card.getColor() == tableCardCurrent.getColor()) {
                if (int(card.getNumber()) >
                    gameManager.getNilaiKartuTertinggi()) {
                    gameManager.setNilaiKartuTertinggi(int(card.getNumber()));
                    gameManager.setNextTurnPlayerIndex(
                        gameManager.getCurrentPlayerIndex());
                }
                gameManager.table.put(currentPlayer.take(card));
            } else {
                throw InvalidCardException();
            }
        } catch (InvalidCardException& e) {
            std::cout << e.what() << '\n';
            return GameState::getState("player turn");
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

    while (!currentPlayer.hasTypeCard(tableCardCurrent)) {
        // if (gameManager.deck.getInventory().empty()){
        //     std::vector<CangkulCard> cards = gameManager.table.takeAll();
        //     for(CangkulCard card : cards){
        //         gameManager.deck.putCard(card);
        //     }
        //     gameManager.deck.shuffle();
        //     }
        currentPlayer.put(gameManager.deck.takeCard());
        // cout << "Player " << gameManager.getCurrentPlayer().getNickname()
        //      << " mengambil kartu!" << endl;
    }
    return GameState::getState("dashboard");
}

CangkulNextPlayer::CangkulNextPlayer(CangkulGameManager& gm)
    : GameState(false), gameManager(gm)
{
}

GameState* CangkulNextPlayer::updateState()
{
    if (gameManager.getCurrentTurnQueue().empty()) {
        return GameState::getState("winner pick card");
    }
    gameManager.nextPlayer();
    // std::string name = gameManager.getCurrentPlayer().getNickname();
    // std::cout << "Giliran dilanjut ke \e[1;93m" + name + "\e[0m" <<
    // std::endl;
    return GameState::getState("dashboard");
}

CangkulWinnerPickCard::CangkulWinnerPickCard(CangkulGameManager& gm)
    : GameState(false), gameManager(gm)
{
}

GameState* CangkulWinnerPickCard::updateState()
{
    gameManager.nextPlayer();
    CangkulPlayer& currentPlayer = gameManager.getCurrentPlayer();
    vector<CangkulCard>& playerCard = currentPlayer.getInventory();
    int index;
    Utils::clear_screen();
    cout << endl;
    cout << "Selamat \e[1;93m" << currentPlayer.getNickname()
         << "\e[0m, kamu menang pada ronde ini!" << endl;
    cout << endl;
    cout << "> Daftar Kartu "
         << "\e[1;93m(" << currentPlayer.getNickname() << ")\e[0m"
         << ": \n";
    currentPlayer.printInventory();
    cout << endl;
    std::cout << "Pilih kartu yang mau dikeluarkan untuk round selanjutnya: \n";
    std::cout << "> ";
    std::cin >> index;
    try {
        CangkulCard card = playerCard[index - 1];
        gameManager.setNilaiKartuTertinggi(int(card.getNumber()));
        gameManager.table.put(currentPlayer.take(card));
    } catch (InvalidCardException& e) {
        std::cout << e.what() << '\n';
        return GameState::getState("winner pick card");
    }

    return GameState::getState("next turn");
}
