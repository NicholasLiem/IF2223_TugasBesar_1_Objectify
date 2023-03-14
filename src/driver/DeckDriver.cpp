#include "Card.hpp"
#include "Deck.hpp"

#include <iostream>
using namespace std;

int main()
{
    Deck<Card> deck;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            deck.putCard(Card(i, j));
        }
    }
    deck.shuffle();
    for (int i = 0; i < 52; i++) {
        Card card = deck.takeCard();
        cout << card << endl;
    }
    return 0;
}
