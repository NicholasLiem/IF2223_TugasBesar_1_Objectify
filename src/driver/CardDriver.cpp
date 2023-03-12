#include "../lib/entities/Card.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    Card c1(CardColor::Red,CardNumber::Three);
    Card c2(CardColor::Green, CardNumber::Three);
    if(c1 == c2){
        cout << "Pair!" << endl;
    }
    if(c1 < c2){
        cout << "C1 lebih kecil dari c2 " << endl;
    }

    if(c1 > c2){
        cout << "C1 lebih besar dari c2" << endl;
    }
    return 0;
}
