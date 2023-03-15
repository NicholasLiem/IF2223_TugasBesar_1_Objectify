#ifndef __STATE_
#define __STATE_

#include "GameManager.hpp"
#include "GameState.hpp"

class Dashboard : public GameState
{
  private:
    GameManager& gameManager;

  public:
    Dashboard(GameManager& gm);

    GameState* updateState() override;
};

class PlayerTurn : public GameState
{
  private:
    GameManager& gameManager;
  public:
    PlayerTurn(GameManager& gm);

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
