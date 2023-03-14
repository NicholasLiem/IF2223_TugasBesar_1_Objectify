#include "../lib/entities/Combo.hpp"
#include <iostream>
#include <vector>
using namespace std;

bool tempCompare(const Card& a,const Card& b){
    return a > b;
}

int main(){
    Card c1(3,8);
    Card c2(3,9);
    Card c3(3,10);
    Card c4(3,11);
    Card c5(3,12);
    Card c6(3,6);
    Card c7(3,13);
    vector <Card> playerCards;
    vector <Card> tableCards;
    tableCards.push_back(c1);tableCards.push_back(c2);tableCards.push_back(c3);tableCards.push_back(c4);tableCards.push_back(c5);
    playerCards.push_back(c6);playerCards.push_back(c7);
   
    Pair *p2;
    p2 = new Pair();
    ThreeOfAKind *t;
    t = new ThreeOfAKind();
    Flush  *f;
    f = new Flush();
    Straight *s;
    s = new Straight();
    Combo *c;
    // c->registerCombo(p2);
    // c->registerCombo(t);
    c->registerCombo(s);
    Combo* combo;
    float value = 0;
    for (Combo* c : Combo::getCombos()) {
        if(c->isThereCombo(playerCards,tableCards)){
            cout << "Ada Combo " << c->getName() << endl;
            cout << c->value() <<endl;
        }else{
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
    return 0;
}