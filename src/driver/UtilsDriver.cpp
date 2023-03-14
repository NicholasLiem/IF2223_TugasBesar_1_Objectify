#include "Card.hpp"
#include "Utils.hpp"

#include <iostream>
#include <vector>

int main()
{
    Card a(CardColor::Red, CardNumber::One);
    Card b(CardColor::Green, CardNumber::Two);
    Card c(CardColor::Yellow, CardNumber::Three);
    Card d(CardColor::Red, CardNumber::Four);

    std::vector<Card> cards = {a, b, c, d};

    std::vector<Card> redCards = Utils::filter_vector<Card>(
        cards, [](const Card& c) { return c.getColor() == CardColor::Red; });

    Utils::forEach(redCards, [](auto&& x) { std::cout << x << "\n"; });

    std::cout << Utils::max<Card>(redCards) << "\n";
    std::cout << Utils::maxBy<Card>(cards, [](const Card& x) {
        return x.getColor() < CardColor::Blue;
    }) << "\n";
}
