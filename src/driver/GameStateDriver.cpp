#include "State.hpp"
#include "Action.hpp"

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
