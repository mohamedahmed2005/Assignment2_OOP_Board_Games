//
// Created by Amr khaled on 12/12/2024.
//

#ifndef FINAL_BOAED_GAME_VERSION_PYRAMID_H
#define FINAL_BOAED_GAME_VERSION_PYRAMID_H

#include <iostream>
#include <vector>
#include "BoardGame_Classes.h"
#include <cctype>
#include <algorithm>

using namespace std;



/// --------------------------------------------------------------------------------- Pyramid board class

template <typename T>
class PyramidBoard : public Board<T> {
private:

    bool is_within_bounds(int x, int y);  // Check if a position is within bounds

public:
    PyramidBoard();  // Constructor
    ~PyramidBoard();  // Destructor to free dynamically allocated memory

    bool update_board(int x, int y, T symbol) override;  // Update the board with a symbol
    void display_board() override;  // Display the pyramid board
    bool is_win() override;  // Check if there is a winner
    bool is_draw() override;  // Check if the game is a draw
    bool game_is_over() override;  // Check if the game is over
};



// Constructor
template <typename T>
PyramidBoard<T>::PyramidBoard() {
    this->rows = 3;  // Pyramid has 3 levels
    this->columns = 5;  // Base row has 5 columns
    this->n_moves = 0;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[2 * i + 1];  // Each row has 2*i+1 columns
        for (int j = 0; j < 2 * i + 1; ++j) {
            this->board[i][j] = '-';  // Initialize all cells to '-'
        }
    }

}

// Destructor
template <typename T>
PyramidBoard<T>::~PyramidBoard() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

// Check bounds
template <typename T>
bool PyramidBoard<T>::is_within_bounds(int x, int y) {
    return x >= 0 && x < this->rows && y >= 0 && y < 2 * x + 1;
}


template <typename T>
bool PyramidBoard<T>::is_win() {
    // horizontal
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != '-')){
        return true;
    }
    //vertical cases
    // second row
    if ((this->board[1][0] == this->board[1][1] && this->board[1][1] == this->board[1][2] && this->board[1][0] != '-')){
        return true;
    }
    // third row
    if ((this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != '-')){
        return true;
    }if ((this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][3] != '-')){
        return true;
    }if ((this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][4] != '-')){
        return true;
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[2][0] != '-') ||
        (this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[2][4] != '-')) {
        return true;
    }

    return false;
}



// Update the board
template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (!is_within_bounds(x, y) || this->board[x][y] != '-') {
//        cout << "Invalid move. Try again.\n";
        return false;
    }
    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
}


template <typename T>
void PyramidBoard<T>::display_board() {
    cout << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3 - i - 1; ++j) {
            cout << "        ";  // 3 spaces for each padding
        }
        // Print the pyramid row elements
        for (int j = 0; j < 1 + (i * 2); ++j) {
            if ((this->board[i][j]) == '-'){
                cout << "[ " << i << ", " << j << " ]"; // print pyramid elements
            }else{
                cout << "[  " << this->board[i][j] << "   ]"; // print pyramid elements
            }
        }

        cout << endl;
    }
}

// Check for a draw
template <typename T>
bool PyramidBoard<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

// Check if the game is over
template <typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}


/// ----------------------------------------------------------------------------------------- Pyramid Player class


template <typename T>
class PyramidPlayer : public Player<T>{
private:
    T** boardPTR2D;
public:
    PyramidPlayer(string n, T symbol) ;
    void getmove(int& x, int& y) override;
};





template <typename T>
PyramidPlayer<T>::PyramidPlayer(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
void PyramidPlayer<T>::getmove(int& x, int& y) {
    string strX, strY;
    cout << this->name << " turn " << endl;
    while (true) {
        cout << "Enter the row: ";
        cin >> strX;

        // Check if the input is numeric
        if (!strX.empty() && all_of(strX.begin(), strX.end(), ::isdigit)) {
            x = stoi(strX); // Convert string to integer
            break;
        } else {
            cout << "Invalid input. Please enter a valid numeric row.\n";
        }
    }

    while (true) {
        cout << "Enter the column: ";
        cin >> strY;

        // Check if the input is numeric
        if (!strY.empty() && all_of(strY.begin(), strY.end(), ::isdigit)) {
            y = stoi(strY); // Convert string to integer
            break;
        } else {
            cout << "Invalid input. Please enter a valid numeric column.\n";
        }
    }
}


/// ----------------------------------------------------------------------------------  Random player Pyramid class

template <typename T>
class PyramidRandomPlayer : public RandomPlayer<T> {
public:
    PyramidRandomPlayer(string n,T symbol);

    // Generates a random move for the pyramid board.
    void getmove(int& x, int& y);
};

template <typename T>
PyramidRandomPlayer<T>::PyramidRandomPlayer(string n, T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = n + "_Habida";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void PyramidRandomPlayer<T>::getmove(int& x, int& y) {
    cout << this->name << " turn " << endl;
    x = rand() % 3;
    y = rand() % 5;

}

void PyramidGameRules(){
    // Print game rules and board shape
    cout << "Game Rules:\n";
    cout << "1- Pyramid Tic-Tac-Toe\n";
    cout << "   - The game board is shaped like a pyramid.\n";
    cout << "   - Players take turns marking Xs and Os as in traditional tic-tac-toe.\n";
    cout << "   - Enter the coordinates (row, column) to place your symbol.\n";
    cout << "Winning:\n";
    cout << "   - The first player to get three-in-a-row vertically, horizontally, or diagonally wins.\n";
    cout << "\nBoard Layout:\n";
    cout << "                  [ 0, 0 ]\n";
    cout << "          [ 1, 0 ][ 1, 1 ][ 1, 2 ]\n";
    cout << "  [ 2, 0 ][ 2, 1 ][ 2, 2 ][ 2, 3 ][ 2, 4 ]\n";
    cout << "\nExamples of Winning Positions:\n";
    cout << "  Diagonal: [0,0], [1,1], [2,2]\n";
    cout << "  Horizontal: [2,0], [2,1], [2,2]\n";
    cout << "  Vertical: [0,0], [1,0], [2,0]\n";
    cout << "-------------------------------------------------\n";


};
/// ---------------------------------------------------------------- Implementation Function
void PyramidGame() {
    PyramidGameRules();




    string choicePlayerType, choiceSymbol;
    Player<char> *players[2];
    Board<char> *pyramid_board = new PyramidBoard<char>();
    string player1Name, player2Name;
    char s1, s2;

    cout << "Welcome to my Pyramid X-O Game.\n";

    // Set up Player 1
    while (true) {
        choicePlayerType = "";
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choicePlayerType: ";
        cin >> choicePlayerType;

        if (choicePlayerType == "1" || choicePlayerType == "2") {
            cout << "Choose your symbol:\n";
            cout << "1. 'X'\n";
            cout << "2. 'O'\n";
            cin >> choiceSymbol;

            if (choiceSymbol == "1") {
                s1 = 'X';
                s2 = 'O';
            } else if (choiceSymbol == "2") {
                s1 = 'O';
                s2 = 'X';
            } else {
                cout << "Invalid symbol choicePlayerType. Please choose 1 or 2.\n";
                continue;
            }

            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            if (choicePlayerType == "1") {
                players[0] = new PyramidPlayer<char>(player1Name, s1);
            } else {
                players[0] = new PyramidRandomPlayer<char>(player1Name, s1);
            }
            break;
        } else {
            cout << "Invalid choicePlayerType. Please choose 1 or 2.\n";
        }
    }

    // Set up Player 2
    while (true) {
        cout << "Enter Player 2 name (different from Player 1): ";
        cin >> player2Name;
        if (player2Name != player1Name) {
            break;
        } else {
            cout << "Player 2 name cannot be the same as Player 1. Try again.\n";
        }
    }

    while (true) {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choicePlayerType: ";
        cin >> choicePlayerType;

        if (choicePlayerType == "1") {
            players[1] = new PyramidPlayer<char>(player2Name, s2);
            break;
        } else if (choicePlayerType == "2") {
            players[1] = new PyramidRandomPlayer<char>(player2Name, s2);
            break;
        } else {
            cout << "Invalid choicePlayerType. Please choose 1 or 2.\n";
        }
    }

    // Assign board to players
    players[0]->setBoard(pyramid_board);
    players[1]->setBoard(pyramid_board);

    // Display game setup
    cout << "(" << players[0]->getname() << ") with symbol (" << players[0]->getsymbol() << ") vs ("
         << players[1]->getname() << ") with symbol (" << players[1]->getsymbol() << ")\n";

    // Run the game
    GameManager<char> pyramidGame(pyramid_board, players);
    pyramidGame.run();

    // Clean up
    delete players[0];
    delete players[1];
    delete pyramid_board;
}

#endif //FINAL_BOAED_GAME_VERSION_PYRAMID_H
