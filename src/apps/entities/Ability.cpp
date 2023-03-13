#include "Ability.hpp"

#include "Deck.hpp"

#include <vector>

Deck<Ability*> Ability::abilities;

void Ability::registerAbility(Ability* ability)
{
    abilities.putCard(ability);
}

void Ability::clearAbilities()
{
    for (auto x : abilities.getAll()) {
        delete x;
    }
    abilities.clear();
}

Ability::Ability(GameManager& game, std::string name) : game(game), name(name)
{
    this->used = false;
    this->muted = false;
}

void Ability::setOwner(Player* player)
{
    owner = player;
}

std::string Ability::getName() const
{
    return name;
}

bool Ability::isUsed() const
{
    return used;
}

bool Ability::isMuted() const
{
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

ReRollCard::ReRollCard(GameManager& game) : Ability(game, "ReRoll Card") {}

void ReRollCard::useAbility()
{
    std::vector<Card> oldCards = this->owner->takeAll();
    owner->put(this->game.deck.takeCard());
    owner->put(this->game.deck.takeCard());
    this->used = true;
}

QuadrupleCard::QuadrupleCard(GameManager& game)
    : Ability(game, "Quadruple Card")
{
}

void QuadrupleCard::useAbility()
{
    game.setPot(game.getPot() * 4);
    this->used = true;
}

QuarterCard::QuarterCard(GameManager& game) : Ability(game, "Quarter Card") {}

void QuarterCard::useAbility()
{
    game.setPot(game.getPot() * 0.25);
    this->used = true;
}

ReverseDirCard::ReverseDirCard(GameManager& game)
    : Ability(game, "Reverse Direction Card")
{
}

void ReverseDirCard::useAbility()
{
    this->game.reverseDirection();
    this->used = true;
}

SwapCard::SwapCard(GameManager& game) : Ability(game, "Swap Card") {}

void SwapCard::useAbility() {}

void SwapCard::useAbility(Player& target, int CardIdx1, int CardIdx2)
{
    Card ownCard = this->owner->get(CardIdx1);
    Card targetCard = target.get(CardIdx2);

    target.take(targetCard);
    target.put(ownCard);

    this->owner->take(ownCard);
    this->owner->put(targetCard);
    this->used = true;
} // maybe right (?)

SwitchCard::SwitchCard(GameManager& game) : Ability(game, "Switch Card") {}

void SwitchCard::useAbility() {}

void SwitchCard::useAbility(Player& target)
{
    std::vector<Card> Player1 = this->owner->takeAll();
    std::vector<Card> Player2 = target.takeAll();

    for (auto& i : Player2) {
        this->owner->put(i);
    }

    for (auto& i : Player1) {
        target.put(i);
    }
    this->used = true;
}

AbilitylessCard::AbilitylessCard(GameManager& game)
    : Ability(game, "Abilityless Card")
{
}

void AbilitylessCard::useAbility() {}

void AbilitylessCard::useAbility(Player& target)
{
    this->game.getAbility(target.getNickname())->mute();
    this->used = true;
}
