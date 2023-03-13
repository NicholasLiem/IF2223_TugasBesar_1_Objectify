#include "Ability.hpp"

#include "Deck.hpp"

#include <vector>

Deck<Ability*> Ability::abilities;

Ability::Ability(GameManager& game, Player& owner, std::string name)
    : game(game), owner(owner), name(name)
{
    this->used = false;
    this->muted = false;
}

std::string Ability::getName() const
{
    return name;
}

bool Ability::isUsed() const {
    return used;
}

bool Ability::isMuted() const {
    return muted;
}

Deck<Ability*>& Ability::getAbilities()
{
    return abilities;
}

void Ability::mute()
{
    this->muted = false;
}

ReRollCard::ReRollCard(GameManager& game, Player& owner)
    : Ability(game, owner, "ReRoll Card")
{
}

void ReRollCard::useAbility()
{
    std::vector<Card> oldCards = this->owner.takeAll();
    owner.put(this->game.deck.takeCard());
    owner.put(this->game.deck.takeCard());
    this->used = true;
}

QuadrupleCard::QuadrupleCard(GameManager& game, Player& owner)
    : Ability(game, owner, "Quadruple Card")
{
}

void QuadrupleCard::useAbility()
{
    game.setPot(game.getPot() * 4);
    this->used = true;
}

QuarterCard::QuarterCard(GameManager& game, Player& owner)
    : Ability(game, owner, "Quarter Card")
{
}

void QuarterCard::useAbility()
{
    game.setPot(game.getPot() * 0.25);
    this->used = true;
}

ReverseDirCard::ReverseDirCard(GameManager& game, Player& owner)
    : Ability(game, owner, "Reverse Direction Card")
{
}

void ReverseDirCard::useAbility()
{
    this->game.reverseDirection();
    this->used = true;
}

SwapCard::SwapCard(GameManager& game, Player& owner)
    : Ability(game, owner, "Swap Card")
{
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

SwitchCard::SwitchCard(GameManager& game, Player& owner)
    : Ability(game, owner, "Switch Card")
{
}

void SwitchCard::useAbility(Player& target)
{
    std::vector<Card> Player1 = this->owner.takeAll();
    std::vector<Card> Player2 = target.takeAll();

    for (auto& i : Player2) {
        this->owner.put(i);
    }

    for (auto& i : Player1) {
        target.put(i);
    }
    this->used = true;
}

AbilitylessCard::AbilitylessCard(GameManager& game, Player& owner)
    : Ability(game, owner, "Abilityless Card")
{
}

void AbilitylessCard::useAbility(Player& target)
{
    this->game.getAbility(target.getNickname())->mute();
    this->used = true;
}
