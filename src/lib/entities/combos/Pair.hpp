#ifndef __PAIR_
#define __PAIR_

#include "Combo.hpp"

#include <vector>
using namespace std;

class Pair : public Combo
{
  public:
    Pair();
    Pair(Pair& other);

    bool isThereCombo(vector<Card>& cards) override;
    Combo* clone() override;
    float value() const override;
};

#endif // !__PAIR_
