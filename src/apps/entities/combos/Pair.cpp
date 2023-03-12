#include "../../../lib/entities/combos/Pair.hpp"
#include <iostream>
using namespace std;

Pair::Pair() : Combo("Pair"){};

Pair::Pair(Pair& other) : Combo(other){};

bool Pair::isThereCombo(vector<Card>& cards){
    for(int i = 0 ; i < cards.size();i++){
        for(int j = i+1; j < cards.size();j++){
            if(cards[i] == cards[j]){
                return true;
            }
        }
    }
    return false;
}

Combo* Pair::clone(){
    for(int i = 0;i < this->getCombos().size();i++){
        this->registerCombo(this->getCombos()[i]);
    }
    return this;
}

float Pair::value()const{
    // Rumus menghitung Pair
}