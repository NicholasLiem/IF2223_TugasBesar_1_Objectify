#ifndef __QUARTERACT_
#define __QUARTERACT_

#include "Action.hpp"

class QuarterAct : public Action
{
  public:
    QuarterAct(GameManager& gameManager);

    GameState* updateState() override;

  private:
    void doAction() override;
};

#endif // !__QUARTERACT_
