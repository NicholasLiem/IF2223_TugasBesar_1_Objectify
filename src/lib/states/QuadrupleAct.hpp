#ifndef __QUADRUPLEACT_
#define __QUADRUPLEACT_

#include "Action.hpp"

class QuadrupleAct : public Action
{
  public:
    QuadrupleAct(GameManager& gameManager);

    GameState* updateState() override;

  private:
    void doAction() override;
};

#endif // !__QUADRUPLEACT_
