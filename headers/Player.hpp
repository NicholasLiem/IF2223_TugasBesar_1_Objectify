#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__
#include <iostream>

class Player: {
  public:
    Player(string name, string nickname, int points);
    void Double();
    void Next();
    void Half();
    void Ability();
  protected:
    string name;
    string nickname;
    int points;
    // Cards* abilityCards;
};

#endif