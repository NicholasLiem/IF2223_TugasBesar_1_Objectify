#ifndef __HALF_
#define __HALF_

#include "Action.hpp"

class Half : public Action
{
  public:
    Half(GameManager& gameManager);

    GameState* updateState() override;

  private:
    void doAction() override;
};

#endif // !__HALF_
