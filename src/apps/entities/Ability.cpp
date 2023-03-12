#include "Ability.hpp"

Ability::Ability(GameManager& game, Player& owner)
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void Ability::useAbility() = 0;

ReRollCard::ReRollCard(GameManager& game, Player& owner)
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void ReRollCard::useAbility()
{
    vector<Card> oldCards = this->owner.takeAll();
    owner.put(this->game.deck.takeCard());
    owner.put(this->game.deck.takeCard());
}

QuadrupleCard::QuadrupleCard(GameManager& game, Player& owner)
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void QuadrupleCard::useAbility()
{
    game.setPot(game.getPot() * 4);
}

QuarterCard::QuarterCard(GameManager& game, Player& owner)
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void QuarterCard::useAbility()
{
    game.setPot(game.getPot() * 0.25);
}

ReverseDirCard::ReverseDirCard(GameManager& game, Player& owner)
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void ReverseDirCard::useAbility()
{
    this->game.reverseDirection();
}

SwapCard::SwapCard(GameManager& game, Player& owner)
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void SwapCard::useAbility() {} // Need implementation

SwitchCard::SwitchCard(GameManager& game, Player& owner)
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void SwitchCard::useAbility(Player& target)
{
    vector<Card> Player1 = this->owner.takeAll();
    vector<Card> Player2 = target.takeAll();

    for (int i = 0; i < Player2.size(); i++) {
        this->owner.put(Player2[i]);
    }

    for (int i = 0; i < Player1.size(); i++) {
        target.put(Player1[i]);
    }
}

AbilityLessCard::AbilityLessCard(GameManager& game, Player& owner)
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void AbilityLessCard::useAbility(vector<Player>& players) {

} // Need implementation