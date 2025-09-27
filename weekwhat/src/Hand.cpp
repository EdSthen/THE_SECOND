#include "Hand.h"
#include <sstream>

Hand::Hand() : score(0), hasAce(false), aceCount(0) {}

void Hand::addCard(const Card& card) {
    cards.push_back(card);
    int cardValue = card.getValue();
    
    if (card.getRank() == Rank::ACE) {
        hasAce = true;
        aceCount++;
    }
    
    score += cardValue;
    
    while (score > 21 && aceCount > 0) {
        score -= 10; // Тузы превращаются в 1
        aceCount--;
    }
}

int Hand::getScore() const {
    return score;
}

void Hand::clear() {
    cards.clear();
    score = 0;
    hasAce = false;
    aceCount = 0;
}

bool Hand::isBusted() const {
    return score > 21;
}

bool Hand::isBlackjack() const {
    return cards.size() == 2 && score == 21;
}

std::string Hand::toString() const {
    std::stringstream ss;
    for (size_t i = 0; i < cards.size(); i++) {
        ss << cards[i].toString();
        if (i < cards.size() - 1) ss << " ";
    }
    ss << " (" << score << ")";
    return ss.str();
}

size_t Hand::getCardCount() const {
    return cards.size();
}

const std::vector<Card>& Hand::getCards() const {
    return cards;
}

bool Hand::getHasAce() const {
    return hasAce;
}