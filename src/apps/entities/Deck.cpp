#include "Deck.hpp"

template <class T>
T Deck<T>::takeCard()
{
    T card = this->inventory.back();
    this->inventory.pop_back();
    return card;
}

template <class T>
T Deck<T>::take(T item)
{
    T card = item;
    auto itr = std::find(this->inventory.begin(), this->inventory.end(), item);
    if (itr != this->inventory.end()) {
        card = *itr;
        this->inventory.erase(itr);
    }
    return card;
}

template <class T>
void Deck<T>::shuffle()
{
    /* Pembangkit Seed */
    std::random_device rd;
    std::mt19937 g(rd());
    /* Shuffling Inventory */
    std::shuffle(this->inventory.begin(), this->inventory.end(), g);
}

template <class T>
void Deck<T>::put(T item)
{
    this->inventory.push_back(item);
}

template <class T>
void Deck<T>::putCard(T card)
{
    this->inventory.push_back(card);
}
