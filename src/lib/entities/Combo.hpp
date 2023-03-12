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
    std::vector<Card> cards;
  private:
    static vector<Combo*> combos;
    const string name;

};

#endif // !__COMBO_
