#ifndef __PLAYERREGIST_
#define __PLAYERREGIST_

#include "GameManager.hpp"
#include "GameState.hpp"

class PlayerRegistration : public GameState
{
  private:
    GameManager& gameManager;

  public:
	PlayerRegistration(GameManager& gameManager);
    
    GameState* updateState() override;
};

#endif // !__PLAYERREGIST_
