#ifndef __COMBO_
#define __COMBO_

#include "Card.hpp"
#include "Valuable.hpp"

#include <string>
#include <vector>

class Combo : public Valuable
{
  public:
    Combo(std::string name);
    Combo(Combo& other);
    virtual ~Combo() = default;

    virtual bool isThereCombo(std::vector<Card>& cards) = 0;
    virtual Combo* clone() = 0;

    static void registerCombo(Combo* combo);
    static void clearCombos();
    static std::vector<Combo*>& getCombos();

  protected:
    std::vector<Card> cards;

  private:
    const std::string name;

    static std::vector<Combo*> combos;
};

#endif // !__COMBO_
