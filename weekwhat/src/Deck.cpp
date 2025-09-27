#include "Deck.h"
#include <iostream>
#include <random>

Deck::Deck() : currentIndex(0) {
    for (int s = 0; s < 4; s++) {
        for (int r = 2; r <= 14; r++) {
            cards.emplace_back(static_cast<Suit>(s), static_cast<Rank>(r));
        }
    }
    shuffle();
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
    currentIndex = 0;
}

Card Deck::dealCard(bool visible) {
    if (currentIndex >= cards.size()) {
        shuffle();
    }
    Card card = cards[currentIndex++];
    card.setVisible(visible);
    return card;
}

void Deck::reset() {
    shuffle();
}

size_t Deck::cardsRemaining() const {
    return cards.size() - currentIndex;
}

double Deck::calculateWinProbability(int currentScore, bool hasAce) const {
    if (currentScore > 21) return 0.0;
    if (currentScore == 21) return 1.0;
    
    int cardsLeft = cardsRemaining();
    if (cardsLeft == 0) return 0.0;
    

    int safeCards = 0;
    int maxSafeValue = 21 - currentScore;
    
    for (int value = 1; value <= 11; value++) {
        if (value <= maxSafeValue) {
            int cardsOfValue = 4;
            if (value == 10) cardsOfValue = 16; // я тут не учел уже вышедшие карты, я не понимаю как избавиться от тонны сопроваждющих ошибок :(
            safeCards += cardsOfValue;
        }
    }
    
    return static_cast<double>(safeCards) / 52.0;
}