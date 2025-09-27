#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

class Hand {
private:
    std::vector<Card> cards;
    int score;
    bool hasAce;
    int aceCount;

public:
    Hand();
    void addCard(const Card& card);
    int getScore() const;
    void clear();
    bool isBusted() const;
    bool isBlackjack() const;
    std::string toString() const;
    size_t getCardCount() const;
    const std::vector<Card>& getCards() const;
    bool getHasAce() const;
};

#endif