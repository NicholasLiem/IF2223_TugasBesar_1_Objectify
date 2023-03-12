#include "../Card.cpp"
#include <iostream>
#include <vector>
using namespace std;

int main(){
    Card *c1;
    c1 = new Card(CardColor::Blue,CardNumber::Two);
    std::vector <Card> temp;
    for(int i = 1; i <= 4;i++){
        for(int j = 1; j <= 13;j++ ){
            temp.push_back(Card(i,j));
        }
    }
    for(int i = 0; i < 52;i++){
        cout << temp[i].value() << endl;
    }
    cout << temp.size() << endl;
    return 0;
}