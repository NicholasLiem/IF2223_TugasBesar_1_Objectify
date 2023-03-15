#ifndef __CANGKULSTATE_
#define __CANGKULSTATE_

#include "CangkulGameManager.hpp"
#include "GameState.hpp"

class CangkulDashboard : public GameState
{
  private:
    CangkulGameManager& gameManager;

  public:
    CangkulDashboard(CangkulGameManager& gm);

    GameState* updateState() override;
};

class CangkulPlayerTurn : public GameState
{
  private:
    CangkulGameManager& gameManager;
  public:
    CangkulPlayerTurn(CangkulGameManager& gm);

    GameState* updateState();
};

class CangkulPlayerRegistration : public GameState
{
  private:
    CangkulGameManager& gameManager;

  public:
    CangkulPlayerRegistration(CangkulGameManager& gameManager);

    GameState* updateState() override;
};

class CangkulConclusion : public GameState
{
  private:
    CangkulGameManager& gameManager;

  public:
    CangkulConclusion(CangkulGameManager& gm);

    GameState* updateState() override;
};

class CangkulPilihKartu : public GameState
{
  private:
    CangkulGameManager& gameManager;

  public:
    CangkulPilihKartu(CangkulGameManager& gm);

    GameState* updateState() override;
};

class CangkulDrawCard : public GameState
{
  private:
    CangkulGameManager& gameManager;

  public:
    CangkulDrawCard(CangkulGameManager& gm);

    GameState* updateState() override;
};

class CangkulNextPlayer : public GameState
{
  private:
    CangkulGameManager& gameManager;

  public:
    CangkulNextPlayer(CangkulGameManager& gm);

    GameState* updateState() override;
};

class CangkulWinnerPickCard : public GameState
{
  private:
    CangkulGameManager& gameManager;

  public:
    CangkulWinnerPickCard(CangkulGameManager& gm);

    GameState* updateState() override;
};

#endif // __STATE_
