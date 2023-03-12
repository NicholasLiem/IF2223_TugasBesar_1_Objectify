#ifndef __ACTION_
#define __ACTION_

#include "GameManager.hpp"
#include "GameState.hpp"

class Action : public GameState
{
  public:
    Action(GameManager& gameManager)
        : GameState(false), gameManager(gameManager)
    {
    }

  protected:
    virtual void doAction() = 0;
    GameManager& gameManager;
};

#endif // !__ACTION_
