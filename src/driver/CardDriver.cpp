#include "Card.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    Card c1 = Card(CardColor::Blue, CardNumber::Two);
    std::vector<Card> temp;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            temp.push_back(Card(i, j));
        }
    }
    for (int i = 0; i < 52; i++) {
        cout << temp[i] << endl;
    }
    cout << temp.size() << endl;
    cin >> c1;
    cout << c1;
    return 0;
}
