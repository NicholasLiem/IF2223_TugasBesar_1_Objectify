#include "../lib/entities/Combo.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    Card c1(2,1);
    Card c2(0,12);
    Card c3(3,14);
    Card c4(1,8);
    Card c5(3,9);
    Card c6(3,12);
    Card c7(3,4);
    vector <Card> playerCards;
    vector <Card> tableCards;
    tableCards.push_back(c1);tableCards.push_back(c2);tableCards.push_back(c3);tableCards.push_back(c4);tableCards.push_back(c5);
    playerCards.push_back(c6);playerCards.push_back(c7);
    Pair *p2;
    p2 = new Pair();
    ThreeOfAKind *t;
    t = new ThreeOfAKind();
    Combo *c;
    c->registerCombo(p2);
    c->registerCombo(t);
    Combo* combo;
    float value = 0;
    for (Combo* c : Combo::getCombos()) {
        if(c->isThereCombo(playerCards,tableCards)){
            cout << "Ada Combo!" << endl;
            cout << c->value() <<endl;
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
    return 0;
}