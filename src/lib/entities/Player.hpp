#ifndef __PLAYER_
#define __PLAYER_

#include "Card.hpp"
#include "InventoryHolder.hpp"

#include <string>


template <class T, class U>
class Player : public InventoryHolder<Card<T,U>>
{
  private:
    std::string nickname;
    long points;

  public:
    Player(std::string nickname);
    Player(const Player<T,U>& other);

    void setPoints(long points);
    void put(Card<T,U> card) override;
    Card<T,U> take(Card<T,U> card) override;
    std::vector<Card<T,U>> takeAll();

    std::string getNickname() const;
    long getPoints() const;
    Card<T,U> operator-(Card<T,U> other);
    void operator+(Card<T,U> other);
    bool operator==(const Player<T,U>& other);
    bool operator<(const Player<T,U>& other);
    bool operator>(const Player<T,U>& other);
    Player<T,U>& operator=(const Player<T,U>& other);
    bool hasTypeCard(Card<T, U> tableCard) const;
    void printInventory();

    template <class T2,class U2>
    friend bool operator==(const Player<T2,U2>& a, const Player<T2,U2>& b);
    friend bool operator==(const Player<CardColor,CardNumber>& a, const Player<CardColor,CardNumber>& b);

    friend bool operator==(const Player<CardSymbol,CangkulNumber>& a, const Player<CardSymbol,CangkulNumber>& b);
    
    template <class T2,class U2>
    friend bool operator< (const Player<T2,U2>& a, const Player<T2,U2>& b);
    template <class T2,class U2>
    friend bool operator> (const Player<T2,U2>& a, const Player<T2,U2>& b);
    template <class T2,class U2>
    friend bool operator!=(const Player<T2,U2>& a, const Player<T2,U2>& b);
    friend bool operator!=(const Player<CardColor,CardNumber>& a, const Player<CardColor,CardNumber>& b);

};

#endif // !__PLAYER_
