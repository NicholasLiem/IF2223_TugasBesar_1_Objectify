#ifndef __COMBO_
#define __COMBO_

#include "Card.hpp"
#include "Valuable.hpp"

// #include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Combo : public Valuable
{
  public:
  
    // Constructor 
    Combo(string name);

    // Copy Constructor
    Combo(Combo& other);

    // Delete constructor
    virtual ~Combo() = default;

    // Function to check if there is any combos
    virtual bool isThereCombo(vector<Card>& cards) = 0;

    // Function to clone a combo
    virtual Combo* clone() = 0;

    // Procedure to add new Combo
    static void registerCombo(Combo* combo);

    // Procedure to delete combo
    static void clearCombos();

    // 
    static vector<Combo*>& getCombos();

  protected:
    vector<Card> cards;

  private:
    static vector<Combo*> combos;
    const string name;

};

// The following classes inherit from the Combo class and implement the isThereCombo()
// and clone() functions in their own specific way

class HighCard : public Combo
{
  public:
    HighCard();
    HighCard(HighCard &other) : Combo(other){};
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value();
};

class Pair: public Combo
{
  public:
    Pair();
    Pair(Pair &other);
    bool isThereCombo(vector<Card>& cards) override;
    Pair* clone() override;
    float value();
};

class TwoPair : public Combo
{
  public:
    TwoPair();
    TwoPair(TwoPair &other);
    bool isThereCombo(vector<Card>& cards) override;
    TwoPair* clone() override;
    float value();
};

class ThreeOfAKind : public Combo
{
  public:
    ThreeOfAKind();
    ThreeOfAKind(ThreeOfAKind &other);
    bool isThereCombo(vector<Card>& cards) override;
    ThreeOfAKind* clone() override;
    float value();
};

class Straight : public Combo
{
  public:
    Straight();
    Straight(Straight &other);
    bool isThereCombo(vector<Card>& cards) override;
    Straight* clone() override;
    float value();
};

class Flush : public Combo
{
  public:
    Flush();
    Flush(Flush &other);
    bool isThereCombo(vector<Card>& cards) override;
    Flush* clone() override;
    float value();
};

class FullHouse : public Combo
{
  public:
    FullHouse();
    FullHouse(FullHouse &other);
    bool isThereCombo(vector<Card>& cards) override;
    FullHouse* clone() override;
    float value();
};

class FourOfAKind : public Combo
{
  public:
    FourOfAKind();
    FourOfAKind(FourOfAKind &other);
    bool isThereCombo(vector<Card>& cards) override;
    FourOfAKind* clone() override;
    float value();
};

class StraightFlush : public Combo
{
  public:
    StraightFlush();
    StraightFlush(StraightFlush &other);
    bool isThereCombo(vector<Card>& cards) override;
    StraightFlush* clone() override;
    float value();
};

#endif // !__COMBO_