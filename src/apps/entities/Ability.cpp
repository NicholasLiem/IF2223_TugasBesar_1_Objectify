#include "Ability.hpp"

Ability::Ability(GameManager& game, Player& owner) : name("Ability Card")
{
    this->game = game;
    this->owner = owner;
    this->used = false;
    this->muted = false;
}

void Ability::useAbility() = 0;

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

void ReRoll::mute()
{
    this->muted = true;
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

void QuadrupleCard::mute()
{
    this->muted = true;
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

void QuarterCard::mute()
{
    this->muted = true;
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

void ReverseDirCard::mute()
{
    this->muted = true;
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
    Card ownCard = this->owner.InventoryHolder::take(CardIdx1);
    Card targetCard = target.InventoryHolder::take(CardIdx2);

    target.take(targetCard);
    target.put(ownCard);

    this->owner.take(ownCard);
    this->owner.put(targetCard);
    this->used = true;
} // maybe right (?)

void SwapCard::mute()
{
    this->muted = true;
}

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

void SwitchCard::mute()
{
    this->muted = true;
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

void AbilitylessCard::mute()
{
    this->muted = true;
}