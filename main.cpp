#include "TicTacToe.h"
#include <iostream>

using namespace std;

int main() {
    GameSignal signal = GameSignal::MENU;

    while (signal != GameSignal::QUIT) {
        TicTacToe game;
        signal = game.playGame();
    }

    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}
