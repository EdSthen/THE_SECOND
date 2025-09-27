#include "Game.h"
#include <iostream>

int main() {
    std::cout << "=== Blackjack ===" << std::endl;
    
    Game game;
    char playAgain = 'y';
    
    while (playAgain == 'y' || playAgain == 'Y') {
        game.playRound();
        
        std::cout << "\nAgain? (y/n): ";
        std::cin >> playAgain;
    }
    
    std::cout << "The end" << std::endl;
    return 0;
}