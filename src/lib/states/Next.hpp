#ifndef __NEXT_
#define __NEXT_

#include "GameManager.hpp"
#include "GameState.hpp"
#include "Action.hpp"
#include "PlayerTurn.hpp"

#include <iostream>

/*
 * Aksi NEXT: selesaikan giliran tanpa melakukan apa-apa.
 */
class Next : public Action
{
  public:
    Next(GameManager& gameManager);

    GameState* updateState() override;
};

#endif // !__NEXT
