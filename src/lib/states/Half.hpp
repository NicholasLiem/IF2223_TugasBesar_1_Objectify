#ifndef __HALF_
#define __HALF_

#include "Action.hpp"

class Half : public Action
{
  public:
    Half(GameManager& gameManager);

    GameState* updateState() override;
};

#endif // !__HALF_
