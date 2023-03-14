#include "Combo.hpp"
#include "Utils.hpp"

#include <iostream>
#include <vector>
using namespace std;

bool tempCompare(const Card& a, const Card& b)
{
    return a > b;
}

int main()
{
    Card c1(0, 12);
    Card c2(0, 11);
    Card c3(0, 10);
    Card c4(1, 8);
    Card c5(0, 9);
    Card c6(0, 7);
    Card c7(0, 8);
    vector<Card> playerCards;
    vector<Card> tableCards;
    tableCards.push_back(c1);
    tableCards.push_back(c2);
    tableCards.push_back(c3);
    tableCards.push_back(c4);
    tableCards.push_back(c5);
    playerCards.push_back(c6);
    playerCards.push_back(c7);

    vector<Card> allCards;
    allCards.insert(allCards.end(), playerCards.begin(), playerCards.end());
    allCards.insert(allCards.end(), tableCards.begin(), tableCards.end());

    cout << "Semua kartu:\n";
    Utils::forEach(allCards, [](auto&& x) { cout << x << "\n"; });

    Combo::registerCombo(new HighCard);
    Combo::registerCombo(new Pair);
    Combo::registerCombo(new TwoPair);
    Combo::registerCombo(new ThreeOfAKind);
    Combo::registerCombo(new Straight);
    Combo::registerCombo(new Flush);
    Combo::registerCombo(new FullHouse);
    Combo::registerCombo(new FourOfAKind);
    Combo::registerCombo(new StraightFlush);

    float value = 0;
    for (Combo* c : Combo::getCombos()) {
        if (c->isThereCombo(playerCards, tableCards)) {
            cout << "Ada Combo " << c->getName() << ", Susunan: ";
            Utils::forEach(c->getCards(), [](auto&& x) { cout << x << ", "; });
            cout << "Nilai: " << c->value() << endl;
        } else {
            cout << "Tidak ada combo " << c->getName() << endl;
        }
    }

    // for(int i = 0 ; i < listCards.size();i++){
    //     int count = 1;
    //     for(int j = i+1; j < listCards.size();j++){
    //         if(listCards[i] == listCards[j]){
    //             cout << listCards[i] << listCards[j];
    //             count++;
    //         }

    //     }
    //     if(count == 2){
    //         cout << "Pair!"<< endl;
    //     }
    // }
    // for(int i = 1; i <19;i++ ){
    //     for(int j = i+1; j < 19;j ++){
    //         cout << listCards[i] << listCards[j] << endl;
    //         if(listCards[i] == listCards[j]){
    //             cout << "Pair" << endl;
    //             cout << listCards[i] << listCards[j] << endl;
    //         }
    //     }
    // }
    Combo::clearCombos();
    return 0;
}
