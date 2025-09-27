#include "Player.h"
#include <iostream>

Player::Player(const std::string& playerName) 
    : name(playerName), isFinished(false) {}

void Player::addCard(const Card& card) {
    hand.addCard(card);
}

void Player::clearHand() {
    hand.clear();
    isFinished = false;
}

int Player::getScore() const {
    return hand.getScore();
}

bool Player::getIsFinished() const {
    return isFinished || hand.isBusted() || hand.getScore() == 21;
}

void Player::setIsFinished(bool finished) {
    isFinished = finished;
}

std::string Player::getName() const {
    return name;
}

std::string Player::getHandString() const {
    return hand.toString();
}

const Hand& Player::getHand() const {
    return hand;
}

double Player::getWinProbability(const Deck& deck) const {
    return deck.calculateWinProbability(getScore(), hand.getHasAce());
}

HumanPlayer::HumanPlayer(const std::string& name) : Player(name) {}

bool HumanPlayer::wantsHit() const {
    if (getIsFinished()) return false;
    
    std::cout << name << ", your hand: " << getHandString() << std::endl;
    std::cout << "Random nubmer: " << (getWinProbability(Deck()) * 100) << "%" << std::endl;
    std::cout << "Draw a catd? (y/n): ";
    
    char response;
    std::cin >> response;
    return response == 'y' || response == 'Y';
}

AIPlayer::AIPlayer(const std::string& name, double risk) 
    : Player(name), riskLevel(risk) {}

bool AIPlayer::wantsHit() const {
    if (getIsFinished()) return false;
    
    int score = getScore();
    double winProb = getWinProbability(Deck());
    
    if (score <= 11) return true;
    if (score >= 17) return false;
    
    return winProb > (0.7 - riskLevel * 0.3);
}

double AIPlayer::getWinProbability(const Deck& deck) const {
    double baseProb = Player::getWinProbability(deck);
    return baseProb;
}