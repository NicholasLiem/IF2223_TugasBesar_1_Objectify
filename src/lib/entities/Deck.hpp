#ifndef __DECK_
#define __DECK_

#include "Card.hpp"
#include "InventoryHolder.hpp"

#include <algorithm>
#include <random>
#include <vector>

template<class T>
class Deck : public InventoryHolder<T>
{
  public:
    void shuffle();
    void putCard(T card);
    T takeCard();

  private:
    void put(T item) override;
    T take(T item) override;
};

#endif // !__DECK_
