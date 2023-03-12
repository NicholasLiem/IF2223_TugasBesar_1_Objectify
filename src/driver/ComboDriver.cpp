#include "../lib/entities/combos/Pair.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    vector<Card> temp;
    for(int i = 0; i < 2;i++){
        for(int j = 0; j < 2;j++){
            temp.push_back(Card(i,j));
        }
    }
    
    return 0;
}