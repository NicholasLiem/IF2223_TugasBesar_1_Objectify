#ifndef __CARD_HPP__
#define __CARD_HPP__
#include <iostream>

class Card: {
  public:
    Card(int id, string color);
    int getID();
    void setID();
    int getColor();
    void setColor();
  protected:
    int id;
    string color;
};
#endif