#include "../lib/entities/Combo.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    Card c1(2,1);
    Card c2(0,12);
    Card c3(3,14);
    Card c4(1,1);
    Card c5(3,9);
    Card c6(3,9);
    Card c7(3,4);
    vector <Card> listCards;
    listCards.push_back(c1);listCards.push_back(c2);listCards.push_back(c3);listCards.push_back(c4);listCards.push_back(c5);
    listCards.push_back(c6);listCards.push_back(c7);
    int pair = 0;
    for(int i = 0; i < listCards.size();i++){
        int count = 1;
        for(int j = i + 1; j < listCards.size();j++){
            if(listCards[i] == listCards[j]){
                count++;
            }
        }
        if(count == 2){
            pair++;
        }
    }
    if(pair == 2){
        cout << "Two Pair!" << endl;
    }else{
        cout << "no pair" << endl;
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