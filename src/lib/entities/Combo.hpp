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
    Combo(const Combo& other);

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
    HighCard(const HighCard& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

class Pair: public Combo
{
  public:
    Pair();
    Pair(const Pair& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

class TwoPair : public Combo
{
  public:
    TwoPair();
    TwoPair(const TwoPair& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

class ThreeOfAKind : public Combo
{
  public:
    ThreeOfAKind();
    ThreeOfAKind(const ThreeOfAKind& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

class Straight : public Combo
{
  public:
    Straight();
    Straight(const Straight& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

class Flush : public Combo
{
  public:
    Flush();
    Flush(const Flush& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

class FullHouse : public Combo
{
  public:
    FullHouse();
    FullHouse(const FullHouse& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

class FourOfAKind : public Combo
{
  public:
    FourOfAKind();
    FourOfAKind(const FourOfAKind& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

class StraightFlush : public Combo
{
  public:
    StraightFlush();
    StraightFlush(const StraightFlush& other);
    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

#endif // !__COMBO_
