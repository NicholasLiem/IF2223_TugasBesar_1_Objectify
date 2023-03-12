#include "Ability.hpp"

Ability::Ability(GameManager& game, Player& owner) : name("Ability Card")
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void Ability::useAbility() = 0;

void Ability::mute()
{
    this->muted = false;
}

ReRollCard::ReRollCard(GameManager& game, Player& owner) : name("ReRoll Card")
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
    this->used = true;
}

QuadrupleCard::QuadrupleCard(GameManager& game, Player& owner)
    : name("Quadruple Card")
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void QuadrupleCard::useAbility()
{
    game.setPot(game.getPot() * 4);
    this->used = true;
}

QuarterCard::QuarterCard(GameManager& game, Player& owner)
    : name("Quarter Card")
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void QuarterCard::useAbility()
{
    game.setPot(game.getPot() * 0.25);
    this->used = true;
}

ReverseDirCard::ReverseDirCard(GameManager& game, Player& owner)
    : name("Reverse Direction Card")
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void ReverseDirCard::useAbility()
{
    this->game.reverseDirection();
    this->used = true;
}
SwapCard::SwapCard(GameManager& game, Player& owner) : name("Swap Card")
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void SwapCard::useAbility(Player& target, int CardIdx1, int CardIdx2)
{
    Card ownCard = this->owner.get(CardIdx1);
    Card targetCard = target.get(CardIdx2);

    target.take(targetCard);
    target.put(ownCard);

    this->owner.take(ownCard);
    this->owner.put(targetCard);
    this->used = true;
} // maybe right (?)

SwitchCard::SwitchCard(GameManager& game, Player& owner) : name("Switch Card")
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

    for (int i : Player2) {
        this->owner.put(Player2[i]);
    }

    for (int i : Player1) {
        target.put(Player1[i]);
    }
    this->used = true;
}

AbilitylessCard::AbilitylessCard(GameManager& game, Player& owner)
    : name("Abilityless Card")
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void AbilitylessCard::useAbility(Player& target)
{
    this->game.getAbility(target.getNickname()).mute();
    this->used = true;
}