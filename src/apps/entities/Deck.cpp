#include "../../lib/entities/Deck.hpp"
#include <iostream>

template<class T>
Deck<T>::Deck(): InventoryHolder<T>(){
    fillDeck();
    shuffle();
}

template<class T>
T Deck<T>::takeCard(){
    T card = this->inventory.back();
    this->inventory.pop_back();
    return card;
}

template<class T>
T Deck<T>::take(T item){
    T card = item;
    auto itr = std::find(this->inventory.begin(), this->inventory.end(), item);
    if(itr != this->inventory.end()){
        card = *itr;
        this->inventory.erase(itr);
    }
    return card;
}

template<class T>
void Deck<T>::shuffle(){
    /* Pembangkit Seed */
    std::random_device rd;
    std::mt19937 g(rd());
    /* Shuffling Inventory */
    std::shuffle(this->inventory.begin(), this->inventory.end(), g);
}

template<class T>
void Deck<T>::put(T item){
    this->inventory.push_back(item);
}

template<class T>
void Deck<T>::putCard(T card){
    this->inventory.push_back(card);
}

template<class T>
void Deck<T>::fillDeck(){
    for(int i = 1; i <= 4;i++){
        for(int j = 1; j <= 13;j++){
            putCard(Card(i, j));
        }
    }
    std::cout << this->inventory.size() << std::endl;
}