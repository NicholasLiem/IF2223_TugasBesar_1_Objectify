#include "../../lib/entities/Deck.hpp"

template<class T>
void Deck<T>::shuffle(){
    /* Pembangkit Seed */
    std::random_device rd;
    std::mt19937 g(rd());
    /* Shuffling Inventory */
    std::shuffle(inventory.begin(), inventory.end(), g);
}

template<class T>
void Deck<T>::put(T item){
    inventory.push_back(item);
}

template<class T>
void Deck<T>::putCard(T card){
    inventory.push_back(card);
}

template<class T>
void Deck<T>::fillDeck(){
    for(int i = 1; i <= 4;i++){
        for(int j = 1; j <= 13;j++){
            putCard(Card(i, j));
        }
    }
}