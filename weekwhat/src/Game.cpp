#include "Game.h"
#include <iostream>
#include <iomanip>

Game::Game() : currentPlayerIndex(0) {
    players.push_back(std::make_unique<HumanPlayer>("Fleshbag"));
    players.push_back(std::make_unique<AIPlayer>("TheGuy", 0.3));
    players.push_back(std::make_unique<AIPlayer>("xXx_TrueGambler777_xXx", 0.7));
}

void Game::addPlayer(std::unique_ptr<Player> player) {
    players.push_back(std::move(player));
}

void Game::startRound() {
    deck.reset();
    
    for (auto& player : players) {
        player->clearHand();
    }
    dealer.clearHand();
    
    for (int i = 0; i < 2; i++) {
        for (auto& player : players) {
            player->addCard(deck.dealCard());
        }
        dealer.addCard(deck.dealCard(i == 0));
    }
    
    currentPlayerIndex = 0;
}

void Game::playRound() {
    std::cout << "=== BEGIN! ===" << std::endl;
    startRound();
    
    for (currentPlayerIndex = 0; currentPlayerIndex < players.size(); currentPlayerIndex++) {
        auto& player = players[currentPlayerIndex];
        
        std::cout << "\n--- " << player->getName() << "'s turn ---" << std::endl;
        displayGameState();
        
        while (!player->getIsFinished() && player->wantsHit()) {
            player->addCard(deck.dealCard());
            std::cout << player->getName() << " draws." << std::endl;
            std::cout << "New hand: " << player->getHandString() << std::endl;
            std::cout << "Random number: " 
                      << std::fixed << std::setprecision(1) 
                      << (player->getWinProbability(deck) * 100) << "%" << std::endl;
            
            if (player->getScore() > 21) {
                std::cout << player->getName() << " overshot!" << std::endl;
                player->setIsFinished(true);
            }
        }
        
        player->setIsFinished(true);
    }
    
    playDealerTurn();
    
    determineWinner();
}

void Game::displayGameState() const {
    std::cout << "\nGameState:" << std::endl;
    std::cout << "Dealer: " << dealer.getHandString() << std::endl;
    
    for (const auto& player : players) {
        std::cout << player->getName() << ": " << player->getHandString();
        std::cout << " [Random number: " << std::fixed << std::setprecision(1) 
                  << (player->getWinProbability(deck) * 100) << "%]";
        
        if (player->getIsFinished()) {
            if (player->getScore() > 21) {
                std::cout << " - Overshot!";
            } else {
                std::cout << " - skip";
            }
        }
        std::cout << std::endl;
    }
}

void Game::playDealerTurn() {
    std::cout << "\n--- Dealer's turn ---" << std::endl;
    std::cout << "Dealer's hand: " << dealer.getHandString(true) << std::endl;
    
    while (dealer.wantsHit()) {
        dealer.addCard(deck.dealCard());
        std::cout << "Dealer draws a card, new hand: " << dealer.getHandString(true) << std::endl;
        
        if (dealer.getScore() > 21) {
            std::cout << "Dealer took too much!" << std::endl;
            break;
        }
    }
}

void Game::determineWinner() const {
    std::cout << "\n=== Round Results ===" << std::endl;
    std::cout << "Dealer: " << dealer.getHandString(true) << std::endl;
    
    int dealerScore = dealer.getScore();
    bool dealerBusted = (dealerScore > 21);
    
    if (dealerBusted) {
        dealerScore = -1;
    }
    
    for (const auto& player : players) {
        int playerScore = player->getScore();
        bool playerBusted = (playerScore > 21);
        
        std::cout << player->getName() << ": " << player->getHandString() << " - ";
        
        if (playerBusted) {
            std::cout << "Lost";
        }
        else if (dealerBusted) {
            std::cout << "WON (Dealer took to much)";
        }
        else if (playerScore > dealerScore) {
            std::cout << "WON";
        }
        else if (playerScore < dealerScore) {
            std::cout << "Lost";
        }
        else {
            std::cout << "Draw";
        }
        
        if (player->getHand().isBlackjack()) {
            std::cout << " [JackBlack!]";
        }
        else if (playerBusted) {
            std::cout << " [Too much]";
        }
        
        std::cout << std::endl;
    }
}

bool Game::allPlayersFinished() const {
    for (const auto& player : players) {
        if (!player->getIsFinished()) return false;
    }
    return true;
}