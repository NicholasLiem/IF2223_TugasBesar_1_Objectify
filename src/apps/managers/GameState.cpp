#include "GameState.hpp"

#include "Exceptions.hpp"

std::map<std::string, GameState*> GameState::states;

GameState::GameState(bool end) : end(end) {}

bool GameState::isEnd() const
{
    return end;
}

void GameState::registerState(std::string name, GameState* state)
{
    states.insert(std::pair<std::string, GameState*>(name, state));
}

GameState* GameState::getState(std::string name)
{
    return states.at(name);
}

void GameState::clearStates()
{
    for (auto x : states) {
        delete x.second;
    }
    states.clear();
}
