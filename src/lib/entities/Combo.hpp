#ifndef __COMBO_
#define __COMBO_

#include "Card.hpp"
#include "Valuable.hpp"

// #include <string>
#include <iostream>
#include <vector>
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
    HighCard(Card c);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

class Pair: public Combo
{
  public:
    Pair(vector<Card> _cards);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

class TwoPair : public Combo
{
  public:
    TwoPair(vector<Card> _cards);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

class ThreeOfAKind : public Combo
{
  public:
    ThreeOfAKind(vector<Card> _cards);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

class Straight : public Combo
{
  public:
    Straight(vector<Card> _cards);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

class Flush : public Combo
{
  public:
    Flush(vector<Card> _cards);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

class FullHouse : public Combo
{
  public:
    FullHouse(vector<Card> _cards);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

class FourOfAKind : public Combo
{
  public:
    FourOfAKind(vector<Card> _cards);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

class StraightFlush : public Combo
{
  public:
    StraightFlush(vector<Card> _cards);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
};

#endif // !__COMBO_