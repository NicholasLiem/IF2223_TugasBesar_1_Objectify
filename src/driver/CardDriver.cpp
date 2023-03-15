#include "../lib/entities/Card.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    Card<CardColor,CardNumber>* c1;
    c1 = new Card(CardColor::Blue, CardNumber::Two);
    std::vector<Card<CardColor,CardNumber>> temp;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 13; j++) {
            temp.push_back(Card<CardColor,CardNumber>(i, j));
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
