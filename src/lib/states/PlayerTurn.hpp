#ifndef __PLAYERTURN_
#define __PLAYERTURN_

#include "GameState.hpp"

class PlayerTurn : public GameState
{
  public:
    PlayerTurn();

    GameState* updateState();
};

#endif // !__PLAYERTURN_
