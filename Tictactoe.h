#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>

using namespace std;

enum class GameSignal { NONE, QUIT, RESTART, MENU };

class TicTacToe {
public:
    TicTacToe();
    ~TicTacToe();

    GameSignal playGame();
    bool       makeMove(int position, char marker);
    bool       checkWinner(char marker);

private:
    char* board;
    int   totalMoves;

    void       displayBoard() const;
    bool       isBoardFull() const;
    bool       isDrawCertain() const;
    int        aiMove(char aiMarker, char humanMarker);
    int        findBestMove(char marker);
    int        getValidInput(const string& prompt, int low, int high);
    GameSignal getMoveInput(const string& prompt, int& outPos);
    GameSignal postGameMenu();
};

#endif