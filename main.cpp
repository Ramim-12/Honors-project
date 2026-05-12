#include "TicTacToe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // seed once at startup

    GameSignal signal = GameSignal::MENU;

    while (signal != GameSignal::QUIT) {
        TicTacToe game;

        do {
            signal = game.playGame();
        } while (signal == GameSignal::RESTART);

        // if MENU ? loop continues (new game created)
        // if QUIT ? loop exits
    }

    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}