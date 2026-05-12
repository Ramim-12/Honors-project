#include "TicTacToe.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <cctype>
#include <random>

using namespace std;

TicTacToe::TicTacToe() {
    board = new char[9];
    resetBoard();
}

TicTacToe::~TicTacToe() {
    delete[] board;
}

void TicTacToe::resetBoard() {
    for (int i = 0; i < 9; ++i)
        board[i] = static_cast<char>('1' + i);
    totalMoves = 0;
}

void TicTacToe::displayBoard() const {
    cout << "\n";
    for (int row = 0; row < 3; ++row) {
        cout << "  ";
        for (int col = 0; col < 3; ++col) {
            cout << " " << board[row * 3 + col] << " ";
            if (col < 2) cout << "|";
        }
        cout << "\n";
        if (row < 2) cout << "  ---+---+---\n";
    }
    cout << "\n";
}

bool TicTacToe::makeMove(int position, char marker) {
    int index = position - 1; // 1-based to 0-based
    if (index < 0 || index > 8) return false;
    if (board[index] == 'X' || board[index] == 'O') return false;
    board[index] = marker;
    ++totalMoves;
    return true;
}

bool TicTacToe::checkWinner(char marker) {
    const int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // rows
        {0,3,6},{1,4,7},{2,5,8}, // columns
        {0,4,8},{2,4,6}          // diagonals
    };
    for (int i = 0; i < 8; ++i)
        if (board[lines[i][0]] == marker &&
            board[lines[i][1]] == marker &&
            board[lines[i][2]] == marker)
            return true;
    return false;
}

bool TicTacToe::isBoardFull() const {
    return totalMoves == 9;
}

bool TicTacToe::isDrawCertain() const {
    const int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int i = 0; i < 8; ++i) {
        bool hasX = false, hasO = false;
        for (int j = 0; j < 3; ++j) {
            if (board[lines[i][j]] == 'X') hasX = true;
            if (board[lines[i][j]] == 'O') hasO = true;
        }
        if (!hasX || !hasO) return false; // line still winnable
    }
    return true;
}

int TicTacToe::findBestMove(char marker) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] != 'X' && board[i] != 'O') {
            char saved = board[i];
            board[i] = marker;
            bool wins = checkWinner(marker);
            board[i] = saved;
            if (wins) return i;
        }
    }
    return -1;
}

int TicTacToe::aiMove(char aiMarker, char humanMarker) {
    int move = findBestMove(aiMarker);
    if (move != -1) return move;

    move = findBestMove(humanMarker);
    if (move != -1) return move;

    if (board[4] != 'X' && board[4] != 'O') return 4;

    for (int c : {0, 2, 6, 8})
        if (board[c] != 'X' && board[c] != 'O') return c;

    for (int e : {1, 3, 5, 7})
        if (board[e] != 'X' && board[e] != 'O') return e;

    return -1;
}

int TicTacToe::getValidInput(const string& prompt, int low, int high) {
    while (true) {
        cout << prompt;
        string token;
        cin >> token;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        try {
            size_t pos;
            int value = stoi(token, &pos);
            if (pos != token.size()) throw invalid_argument("");
            if (value < low || value > high)
                cout << "  Please enter a number between " << low << " and " << high << ".\n";
            else
                return value;
        }
        catch (const invalid_argument&) { cout << "  Invalid input.\n"; }
        catch (const out_of_range&) { cout << "  Number out of range.\n"; }
    }
}

GameSignal TicTacToe::getMoveInput(const string& prompt, int& outPos) {
    while (true) {
        cout << prompt;
        string token;
        cin >> token;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (token.size() == 1) {
            char c = static_cast<char>(toupper(token[0]));
            if (c == 'X') return GameSignal::QUIT;
            if (c == 'R') return GameSignal::RESTART;
            if (c == 'M') return GameSignal::MENU;
        }

        try {
            size_t pos;
            int value = stoi(token, &pos);
            if (pos != token.size()) throw invalid_argument("");
            if (value < 1 || value > 9)
                cout << "  Please enter 1-9, or X / R / M.\n";
            else {
                outPos = value;
                return GameSignal::NONE;
            }
        }
        catch (const invalid_argument&) { cout << "  Invalid input. Enter 1-9, or X / R / M.\n"; }
        catch (const out_of_range&) { cout << "  Number out of range.\n"; }
    }
}

GameSignal TicTacToe::postGameMenu() {
    cout << "  R - Restart match   M - Main menu   X - Quit\n";
    while (true) {
        cout << "  Your choice: ";
        string token;
        cin >> token;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (!token.empty()) {
            char c = static_cast<char>(toupper(token[0]));
            if (c == 'R') return GameSignal::RESTART;
            if (c == 'M') return GameSignal::MENU;
            if (c == 'X') return GameSignal::QUIT;
        }
        cout << "  Please enter R, M, or X.\n";
    }
}

GameSignal TicTacToe::playGame() {
    cout << "========================================\n";
    cout << "         TIC-TAC-TOE  (C++ OOP)\n";
    cout << "========================================\n";
    cout << "  [X] Quit   [R] Restart match   [M] Menu\n\n";

    int mode = getValidInput("Select mode - 1: Player vs Player   2: Player vs AI : ", 1, 2);
    bool vsAI = (mode == 2);

    string player1Name, player2Name;

    cout << "Enter name for Player 1 (X): ";
    getline(cin, player1Name);
    if (player1Name.empty()) player1Name = "Player 1";

    int firstPlayer; // 0 = X slot, 1 = O slot

    if (vsAI) {
        player2Name = "Computer";
        cout << "You will face the Computer (O).\n";
        int choice = getValidInput("Who goes first? 1: You   2: Computer : ", 1, 2);
        firstPlayer = (choice == 1) ? 0 : 1;
    }
    else {
        cout << "Enter name for Player 2 (O): ";
        getline(cin, player2Name);
        if (player2Name.empty()) player2Name = "Player 2";
        random_device rd;
        mt19937 rng(rd());
        firstPlayer = static_cast<int>(rng() % 2);
    }

    char markers[2] = { 'X', 'O' };
    string names[2] = { player1Name, player2Name };

    // Outer loop: RESTART resets the board and replays with the same settings
    while (true) {
        resetBoard();
        int currentPlayer = firstPlayer;
        GameSignal turnSignal = GameSignal::NONE;

        cout << "\n" << names[currentPlayer] << " goes first!\n";

        // Turn loop
        while (true) {
            displayBoard();

            char myMarker = markers[currentPlayer];
            char otherMarker = markers[1 - currentPlayer];
            string& myName = names[currentPlayer];

            // Determine if this slot is AI (only slot 1 in AI mode)
            bool isAITurn = (vsAI && currentPlayer == 1);

            if (isAITurn) {
                cout << myName << " is thinking...\n";
                int idx = aiMove(myMarker, otherMarker);
                cout << myName << " plays at position " << (idx + 1) << ".\n";
                board[idx] = myMarker;
                ++totalMoves;
            }
            else {
                // Human turn: get a valid move or a hotkey signal
                while (true) {
                    int pos = 0;
                    turnSignal = getMoveInput(
                        myName + " (" + myMarker + "), choose [1-9] or X/R/M: ", pos);
                    if (turnSignal != GameSignal::NONE) break; // hotkey pressed
                    if (makeMove(pos, myMarker))        break; // valid move placed
                    cout << "  That cell is already taken.\n";
                }
                if (turnSignal != GameSignal::NONE) break; // exit turn loop
            }

            if (checkWinner(myMarker)) {
                displayBoard();
                cout << "*** " << myName << " wins! Congratulations! ***\n\n";
                turnSignal = postGameMenu();
                break;
            }

            if (isBoardFull()) {
                displayBoard();
                cout << "*** It's a draw! ***\n\n";
                turnSignal = postGameMenu();
                break;
            }

            if (isDrawCertain()) {
                displayBoard();
                cout << "*** No one can win from here - it's a draw! ***\n\n";
                turnSignal = postGameMenu();
                break;
            }

            currentPlayer = 1 - currentPlayer;
        }

        // Handle signal from turn loop
        if (turnSignal == GameSignal::RESTART) {
            cout << "\n--- Restarting match ---\n";
            continue; // loop back: resetBoard, same names/mode/firstPlayer
        }
        return turnSignal; // QUIT or MENU -> back to main
    }
}
