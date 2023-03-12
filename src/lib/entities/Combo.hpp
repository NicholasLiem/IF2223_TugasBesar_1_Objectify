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
    std::vector<Card> cards;

  private:
    const string name;

    static vector<Combo*> combos;
};

#endif // !__COMBO_
