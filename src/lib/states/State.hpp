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

class CardCalculation : public GameState
{
  private:
    GameManager& gameManager;

  public:
    CardCalculation(GameManager& gm);

    GameState* updateState() override;
};

class Conclusion : public GameState
{
  private:
    GameManager& gameManager;

  public:
    Conclusion(GameManager& gm);

    GameState* updateState() override;
};

class End : public GameState
{
  public:
    End();
    GameState* updateState() override;
};



#endif // __STATE_
