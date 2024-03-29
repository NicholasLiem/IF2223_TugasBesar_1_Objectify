#include "Ability.hpp"

#include "Deck.hpp"

#include <vector>

Deck<Ability*> Ability::abilities;

void Ability::reset()
{
    for (Ability* a : abilities.getAll()) {
        a->muted = false;
        a->used = false;
        a->owner = NULL;
    }
}

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

void Ability::setOwner(MainPlayer* player)
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

void Ability::setUsed(bool value)
{
    used = value;
}

void Ability::setMuted(bool value)
{
    muted = value;
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
    this->muted = true;
}

ReRollCard::ReRollCard(GameManager& game) : Ability(game, "ReRoll Card") {}

void ReRollCard::useAbility()
{
    std::vector<MainCard> oldCards = this->owner->takeAll();
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
    if (game.getPot() >= 4){
        game.setPot(game.getPot() * 0.25);
    } else {
        game.setPot(1);
    }
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

void SwapCard::useAbility(MainPlayer& target1, MainPlayer& target2, int CardIdx1,
                          int CardIdx2)
{
    MainCard target1Card = target1.get(CardIdx1);
    MainCard target2Card = target2.get(CardIdx2);

    target1.take(target1Card);
    target1.put(target2Card);

    target2.take(target2Card);
    target2.put(target1Card);
    this->used = true;
} // maybe right (?)

SwitchCard::SwitchCard(GameManager& game) : Ability(game, "Switch Card") {}

void SwitchCard::useAbility() {}

void SwitchCard::useAbility(MainPlayer& target)
{
    std::vector<MainCard> Player1 = this->owner->takeAll();
    std::vector<MainCard> Player2 = target.takeAll();

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

void AbilitylessCard::useAbility(MainPlayer& target)
{
    Ability& ability = *game.getAbility(target.getNickname());
    ability.mute();
    this->used = true;
}
