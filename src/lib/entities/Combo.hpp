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
    Combo(string name);
    Combo(Combo& other);
    virtual ~Combo() = default;

    virtual bool isThereCombo(vector<Card>& cards) = 0;
    virtual Combo* clone() = 0;

    static void registerCombo(Combo* combo);
    static void clearCombos();
    static vector<Combo*>& getCombos();

  protected:
    vector<Card> cards;

  private:
    const string name;

    static vector<Combo*> combos;
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