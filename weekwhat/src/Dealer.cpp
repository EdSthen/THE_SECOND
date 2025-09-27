#include "Dealer.h"

Dealer::Dealer() : Player("House") {}

bool Dealer::wantsHit() const {
    return getScore() < 17;
}

std::string Dealer::getHandString(bool showAll) const {
    if (showAll) {
        return hand.toString();
    }
    
    std::string result = hand.getCards()[0].toString() + " XX";
    return result;
}