/*
    Mini Game Project - Tic Tac Toe
    --------------------------------
    A console based Tic Tac Toe game in C++ demonstrating loops,
    arrays, and conditional logic.

    Modes:
        1. Two Player (Player vs Player)
        2. Player vs Computer

    The board is redrawn after every move, the game detects wins,
    losses and draws, and asks the player if they want to replay
    at the end of each round.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

// board cells hold '1'..'9' before a move is made, or 'X'/'O' after
char board[9];

void resetBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
}

void displayBoard() {
    cout << "\n";
    for (int row = 0; row < 3; row++) {
        cout << "   " << board[row * 3] << " | " << board[row * 3 + 1] << " | " << board[row * 3 + 2] << "\n";
        if (row < 2) cout << "  ---+---+---\n";
    }
    cout << "\n";
}

// all 8 possible winning lines as index triplets
const int WIN_LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
    {0, 4, 8}, {2, 4, 6}             // diagonals
};

bool checkWin(char symbol) {
    for (int i = 0; i < 8; i++) {
        int a = WIN_LINES[i][0], b = WIN_LINES[i][1], c = WIN_LINES[i][2];
        if (board[a] == symbol && board[b] == symbol && board[c] == symbol) {
            return true;
        }
    }
    return false;
}

bool isBoardFull() {
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') return false;
    }
    return true;
}

bool isValidMove(int pos) {
    // pos is 1-9; the cell must still hold its original number (i.e. not taken)
    if (pos < 1 || pos > 9) return false;
    return board[pos - 1] != 'X' && board[pos - 1] != 'O';
}

int getPlayerMove(int playerNum, char symbol) {
    int pos;
    while (true) {
        cout << "Player " << playerNum << " (" << symbol << "), enter your move (1-9): ";
        if (!(cin >> pos)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number.\n";
            continue;
        }

        if (!isValidMove(pos)) {
            cout << "That's not a valid move. Try again.\n";
            continue;
        }
        return pos;
    }
}

// simple heuristic AI:
// 1) win if possible, 2) block opponent's win, 3) take center,
// 4) take a corner, 5) take any free cell
int getComputerMove(char computerSymbol, char opponentSymbol) {
    // 1. try to win
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char backup = board[i];
            board[i] = computerSymbol;
            bool wins = checkWin(computerSymbol);
            board[i] = backup;
            if (wins) return i + 1;
        }
    }

    // 2. block opponent's win
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char backup = board[i];
            board[i] = opponentSymbol;
            bool wins = checkWin(opponentSymbol);
            board[i] = backup;
            if (wins) return i + 1;
        }
    }

    // 3. take center
    if (board[4] != 'X' && board[4] != 'O') return 5;

    // 4. take a corner
    int corners[4] = {0, 2, 6, 8};
    vector<int> freeCorners;
    for (int i = 0; i < 4; i++) {
        int idx = corners[i];
        if (board[idx] != 'X' && board[idx] != 'O') freeCorners.push_back(idx);
    }
    if (!freeCorners.empty()) {
        return freeCorners[rand() % freeCorners.size()] + 1;
    }

    // 5. any free cell
    vector<int> freeCells;
    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') freeCells.push_back(i);
    }
    return freeCells[rand() % freeCells.size()] + 1;
}

void playTwoPlayer() {
    resetBoard();
    int currentPlayer = 1;
    char symbol = 'X';

    displayBoard();

    while (true) {
        int pos = getPlayerMove(currentPlayer, symbol);
        board[pos - 1] = symbol;
        displayBoard();

        if (checkWin(symbol)) {
            cout << "Player " << currentPlayer << " (" << symbol << ") wins! Congratulations!\n";
            break;
        }

        if (isBoardFull()) {
            cout << "It's a draw! Good game.\n";
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        symbol = (symbol == 'X') ? 'O' : 'X';
    }
}

void playVsComputer() {
    resetBoard();
    displayBoard();

    char humanSymbol = 'X';
    char computerSymbol = 'O';
    bool humanTurn = true;

    while (true) {
        if (humanTurn) {
            int pos = getPlayerMove(1, humanSymbol);
            board[pos - 1] = humanSymbol;
        } else {
            cout << "Computer is making a move...\n";
            int pos = getComputerMove(computerSymbol, humanSymbol);
            board[pos - 1] = computerSymbol;
        }

        displayBoard();

        char justPlayed = humanTurn ? humanSymbol : computerSymbol;
        if (checkWin(justPlayed)) {
            if (humanTurn) cout << "You win! Well played.\n";
            else cout << "The computer wins this round. Better luck next time!\n";
            break;
        }

        if (isBoardFull()) {
            cout << "It's a draw! Good game.\n";
            break;
        }

        humanTurn = !humanTurn;
    }
}

void showModeMenu() {
    cout << "\n============================================\n";
    cout << "              TIC TAC TOE\n";
    cout << "============================================\n";
    cout << "1. Two Player (Player vs Player)\n";
    cout << "2. Player vs Computer\n";
    cout << "3. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int choice;
    char again;

    do {
        showModeMenu();
        cin >> choice;

        if (choice == 1) {
            playTwoPlayer();
        } else if (choice == 2) {
            playVsComputer();
        } else if (choice == 3) {
            cout << "\nThanks for playing! Goodbye.\n";
            break;
        } else {
            cout << "Invalid choice, please try again.\n";
            continue;
        }

        cout << "\nPlay again? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    if (choice != 3) cout << "\nThanks for playing! Goodbye.\n";

    return 0;
}
