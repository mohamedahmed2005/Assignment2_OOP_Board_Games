#ifndef _X_O_5X5_H
#define _X_O_5X5_H

#include "BoardGame_Classes.h"
template <typename T>
class X_O_5x5_Board :public Board<T> {
public:
    X_O_5x5_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};


template <typename T>
class X_O_5x5_Player : public Player<T> {
public:
    X_O_5x5_Player(string name, T symbol);
    void getmove(int& x, int& y);

};


template <typename T>
class X_O_5x5_Random_Player : public RandomPlayer<T> {
public:
    X_O_5x5_Random_Player(T symbol);
    void getmove(int& x, int& y);
};



//--------------------------------------- IMPLEMENTATION 

#include <iostream>
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <cctype>

int valid_moves = 0;

//   X_O_5x5_Board IMPLEMENTATION

template <typename T>
X_O_5x5_Board<T>::X_O_5x5_Board() {
    this->rows = this->columns = 5;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_5x5_Board<T>::update_board(int x, int y, T mark) {
    // make a fake move to check if player 1 is the winner
    if (this->n_moves == 24) {
        this->n_moves++;
        return true;
    }
    // Only update if move is valid
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->n_moves++;
        valid_moves = this->n_moves;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_5x5_Board<T>::display_board() {
    cout << "\n   ";
    for (int j = 0; j < this->columns; ++j) {
        cout << "   " << j << "   "; // Column headers with extra spacing
    }
    cout << "\n   " << string(this->columns * 8 + 1, '-') << "\n";

    for (int i = 0; i < this->rows; ++i) {
        cout << i << " |"; // Row header
        for (int j = 0; j < this->columns; ++j) {
            if (i == 0 && j == 4) {
                cout << " EMPTY |";
            }
            else {
                if (this->board[i][j] == ' ') {
                    cout << " (" << i << "," << j << ") |";
                }
                else {
                    cout << "   " << this->board[i][j] << "   |";
                }
            }
        }
        cout << "\n   " << string(this->columns * 8 + 1, '-') << "\n";
    }
    cout << "\n";
}



// Returns true if there is any winner
template <typename T>
bool X_O_5x5_Board<T>::is_win() {
    int player1_score = 0;
    int player2_score = 0;
    // count the number of three in a row after reaching 24  or 25 moves
    if (this->n_moves == 24 || this ->n_moves == 25) {
        // Check rows for three in a row
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j <= this->columns - 3; ++j) {
                if (this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2] &&
                    this->board[i][j] != ' ') {
                    this->board[i][j] == 'X' ? ++player1_score : ++player2_score;
                }
            }
        }

        // Check columns for three in a row
        for (int j = 0; j < this->columns; ++j) {
            for (int i = 0; i <= this->rows - 3; ++i) {
                if (this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j] &&
                    this->board[i][j] != ' ') {
                    this->board[i][j] == 'X' ? ++player1_score : ++player2_score;
                }
            }
        }

        // Check top-left to bottom-right diagonals for three in a row
        for (int i = 0; i <= this->rows - 3; ++i) {
            for (int j = 0; j <= this->columns - 3; ++j) {
                if (this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2] &&
                    this->board[i][j] != ' ') {
                    this->board[i][j] == 'X' ? ++player1_score : ++player2_score;
                }
            }
        }

        // Check top-right to bottom-left diagonals for three in a row
        for (int i = 0; i <= this->rows - 3; ++i) {
            for (int j = 2; j < this->columns; ++j) {
                if (this->board[i][j] == this->board[i + 1][j - 1] &&
                    this->board[i][j] == this->board[i + 2][j - 2] &&
                    this->board[i][j] != ' ') {
                    this->board[i][j] == 'X' ? ++player1_score : ++player2_score;
                }
            }
        }
        if ( this->n_moves == 24 && player2_score > player1_score) {
            cout << "Player 1 score: " << player1_score << "\nPlayer 2 score: " << player2_score << "\n";
            return true;
        }
        if (this->n_moves == 25) {
            cout << "Player 1 score: " << player1_score << "\nPlayer 2 score " << player2_score << "\n";
            if (player1_score > player2_score) {
                return true;
            }
        }
    }
    
    return false;
}

template <typename T>
bool X_O_5x5_Board<T>::is_draw() {

    return (this->n_moves == 25 && !is_win());
}

template <typename T>
bool X_O_5x5_Board<T>::game_is_over() {
    return this->n_moves == 25;
}

//--------------------------------------
//   X_O_5x5_Player IMPLEMENTATION

template <typename T>
X_O_5x5_Player<T>::X_O_5x5_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_5x5_Player<T>::getmove(int& x, int& y) {
    if (valid_moves == 24) {
        valid_moves = 0;
        return;
    }

    while (true) {
        cout << "\nGame rules: the cell you choose must be empty and Cell(0,4) must remain empty\n";
        cout<< this->getname() << " turn. Your symbol is " << this->getsymbol();
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";

        // Check if input is valid
        if (!(cin >> x >> y)) {
            // Clear error flag
            cin.clear();

            // Discard invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter two integers.\n";
            continue;
        }
        if (x < 0 || x  > 4 || y < 0 || y > 4 || (x == 0 && y == 4)) {
            cout << "Invalid move. Coordinates must be between 0 and 4.\n";
            continue;
        }
        break;
    }
}

//--------------------------------------
//   X_O_5x5_Random_Player IMPLEMENTATION

// Constructor for X_O_5x5_Random_Player
template <typename T>
X_O_5x5_Random_Player<T>::X_O_5x5_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void X_O_5x5_Random_Player<T>::getmove(int& x, int& y) {
    do {
        // Random number between 0 and 4
        x = rand() % this->dimension;  
        y = rand() % this->dimension;
    } while (x == 0 && y == 4);
}

#endif
