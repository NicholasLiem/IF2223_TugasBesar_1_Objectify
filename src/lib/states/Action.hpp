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
    GameManager& gameManager;
};

class Double : public Action
{
  public:
    Double(GameManager& gameManager);

    GameState* updateState() override;
};

class Half : public Action
{
  public:
    Half(GameManager& gameManager);

    GameState* updateState() override;
};

/*
 * Aksi NEXT: selesaikan giliran tanpa melakukan apa-apa.
 */
class Next : public Action
{
  public:
    Next(GameManager& gameManager);

    GameState* updateState() override;
};

class QuadrupleAct : public Action
{
  public:
    QuadrupleAct(GameManager& gameManager);

    GameState* updateState() override;
};

class QuarterAct : public Action
{
  public:
    QuarterAct(GameManager& gameManager);

    GameState* updateState() override;
};

class ReRollAct : public Action
{
  public:
    ReRollAct(GameManager& gameManager);

    GameState* updateState() override;
};

class ReverseDirAct : public Action
{
  public:
    ReverseDirAct(GameManager& gameManager);

    GameState* updateState() override;
};

#endif // !__ACTION_
