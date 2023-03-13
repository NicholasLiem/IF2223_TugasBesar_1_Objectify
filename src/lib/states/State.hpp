#ifndef __STATE_
#define __STATE_

#include "GameState.hpp"
#include "GameManager.hpp"

class PlayerTurn : public GameState
{
  public:
    PlayerTurn();

    GameState* updateState();
};

class PlayerRegistration : public GameState
{
  private:
    GameManager& gameManager;

  public:
    PlayerRegistration(GameManager& gameManager);

    GameState* updateState() override;
};

#endif // __STATE_
