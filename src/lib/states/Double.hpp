#ifndef __DOUBLE_
#define __DOUBLE_

#include "Action.hpp"

class Double : public Action
{
  public:
    Double(GameManager& gameManager);

    GameState* updateState() override;

  private:
    void doAction() override;
};

#endif // !__DOUBLE_
