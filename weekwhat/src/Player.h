#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include "Deck.h"
#include <string>

class Player {
protected:
    std::string name;
    Hand hand;
    bool isFinished;

public:
    Player(const std::string& playerName);
    virtual ~Player() = default;
    
    virtual bool wantsHit() const = 0;
    void addCard(const Card& card);
    void clearHand();
    int getScore() const;
    bool getIsFinished() const;
    void setIsFinished(bool finished);
    std::string getName() const;
    std::string getHandString() const;
    const Hand& getHand() const;
    virtual double getWinProbability(const Deck& deck) const;
};

class HumanPlayer : public Player {
public:
    HumanPlayer(const std::string& name);
    bool wantsHit() const override;
};

class AIPlayer : public Player {
private:
    double riskLevel;

public:
    AIPlayer(const std::string& name, double risk = 0.5);
    bool wantsHit() const override;
    double getWinProbability(const Deck& deck) const override;
};

#endif