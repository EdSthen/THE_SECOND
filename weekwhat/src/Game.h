#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Dealer.h"
#include "Deck.h"
#include <vector>
#include <memory>

class Game {
private:
    std::vector<std::unique_ptr<Player>> players;
    Dealer dealer;
    Deck deck;
    int currentPlayerIndex;

public:
    Game();
    void addPlayer(std::unique_ptr<Player> player);
    void startRound();
    void playRound();
    void displayGameState() const;
    void determineWinner() const;
    bool allPlayersFinished() const;
    void playDealerTurn();
};

#endif