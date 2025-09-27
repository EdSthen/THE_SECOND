#include "Card.h"
#include <map>
#include <sstream>

Card::Card(Suit s, Rank r) : suit(s), rank(r), visible(true) {}

int Card::getValue() const {
    if (rank == Rank::JACK || rank == Rank::QUEEN || rank == Rank::KING) {
        return 10; //Вроде прям точных правил нет, поэтому они по 10 все
    } else if (rank == Rank::ACE) {
        return 11; // Костыль, все 11 будут обработаны позже
    }
    return static_cast<int>(rank);
}

std::string Card::toString() const {
    if (!visible) return "XX";
    
    std::map<Suit, std::string> suitSymbols = {
        {Suit::HEARTS, "♥"}, {Suit::DIAMONDS, "♦"}, 
        {Suit::CLUBS, "♣"}, {Suit::SPADES, "♠"}
    };
    
    std::map<Rank, std::string> rankNames = {
        {Rank::TWO, "2"}, {Rank::THREE, "3"}, {Rank::FOUR, "4"}, 
        {Rank::FIVE, "5"}, {Rank::SIX, "6"}, {Rank::SEVEN, "7"},
        {Rank::EIGHT, "8"}, {Rank::NINE, "9"}, {Rank::TEN, "10"},
        {Rank::JACK, "J"}, {Rank::QUEEN, "Q"}, {Rank::KING, "K"},
        {Rank::ACE, "A"}
    };
    
    return rankNames[rank] + suitSymbols[suit];
}

void Card::setVisible(bool v) { visible = v; }
bool Card::isVisible() const { return visible; }
Suit Card::getSuit() const { return suit; }
Rank Card::getRank() const { return rank; }