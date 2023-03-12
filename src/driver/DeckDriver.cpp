#include "../apps/entities/Deck.cpp"
#include "../apps/entities/Card.cpp"
#include <iostream>
using namespace std;

int main(){
    Deck<Card> deck;
    for(int i = 0; i < 52; i++){
        Card card = deck.takeCard();
        cout << card << endl;
    }
    return 0;
}