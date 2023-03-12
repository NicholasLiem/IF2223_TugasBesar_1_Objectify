#include "Double.hpp"
#include "GameManager.hpp"
#include "GameState.hpp"
#include "Half.hpp"
#include "Next.hpp"
#include "PlayerTurn.hpp"
#include "QuadrupleAct.hpp"
#include "QuarterAct.hpp"

int main()
{
    GameManager gm;
    GameState::registerState("player turn", new PlayerTurn);
    GameState::registerState("double", new Double(gm));
    GameState::registerState("next", new Next(gm));
    GameState::registerState("half", new Half(gm));
    GameState::registerState("quadruple", new QuadrupleAct(gm));
    GameState::registerState("quarter", new QuarterAct(gm));

	GameState::clearStates();
    return 0;
}
