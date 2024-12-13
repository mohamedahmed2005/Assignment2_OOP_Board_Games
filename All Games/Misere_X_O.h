#ifndef _MISERE_X_O_H
#define _MISERE_X_O_H

#include "BoardGame_Classes.h"


template <typename T>
class Misere_X_O_Board :public Board<T> {
public:
    Misere_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Misere_X_O_Player : public Player<T> {
public:
    Misere_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class Misere_X_O_Random_Player : public RandomPlayer<T> {
public:
    Misere_X_O_Random_Player(string n,T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION 

#include <iostream>
#include <string>
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <cctype>
bool lose = false;
int Moves = 0;
//   Misere_X_O_Board IMPLEMENTATION
template <typename T>
Misere_X_O_Board<T>::Misere_X_O_Board() {
    this->rows = this->columns = 3;
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
bool Misere_X_O_Board<T>::update_board(int x, int y, T mark) {
    if (lose) {
        return true;
    }
    if (this->n_moves == 9) {
        this->n_moves++;
        return true;
    }
    // Only update if move is valid
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->n_moves++;
        Moves = this->n_moves;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Misere_X_O_Board<T>::display_board() {
    if (lose || this->n_moves == 10) {
        return;
    }
    cout << "\n   ";
    for (int j = 0; j < this->columns; ++j) {
        cout << "   " << j << "   "; // Column headers with extra spacing
    }
    cout << "\n   " << string(this->columns * 8 + 1, '-') << "\n";

    for (int i = 0; i < this->rows; ++i) {
        cout << i << " |"; // Row header
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == ' ') {
                cout << " (" << i << "," << j << ") |";
            }
            else {
                cout << "   " << this->board[i][j] << "   |";
            }
        }
        cout << "\n   " << string(this->columns * 8 + 1, '-') << "\n";
    }
    cout << "\n";
}

// Returns true if there is any winner
template <typename T>
bool Misere_X_O_Board<T>::is_win() {
    if (lose) {
        lose = false;
        return true;
    }
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != ' ') ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != ' ')) {
            lose = true;
            break;
        }
    }

    // Check diagonals
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != ' ') ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != ' ')) {
        lose = true;
    }

    return false;
}
// Return true if 9 moves are done and no winner
template <typename T>
bool Misere_X_O_Board<T>::is_draw() {
    return (this->n_moves == 10 && !is_win());
}

template <typename T>
bool Misere_X_O_Board<T>::game_is_over() {
    return this ->n_moves > 10;
}

//--------------------------------------
//   Misere_X_O_Player IMPLEMENTATION

// Constructor for Misere_X_O_Player
template <typename T>
Misere_X_O_Player<T>::Misere_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Misere_X_O_Player<T>::getmove(int& x, int& y) {
    if (lose || Moves == 9) {
        Moves = 0;
        return;
    }
    while (true) {
        cout << "\nThe cell you choose must be empty\n";
        cout << this->getname() << " turn. Your symbol is " << this->getsymbol();
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";

        // Check if input is valid
        if (!(cin >> x >> y)) {
            // Clear error flag
            cin.clear();

            // Discard invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter two integers.\n";
            continue;
        }
        if (x < 0 || x  > 2 || y < 0 || y > 2) {
            cout << "Invalid move. Coordinates must be between 0 and 2.\n";
            continue;
        }
        break;
    }
}

//--------------------------------------
//   Misere_X_O_Random_Player IMPLEMENTATION

// Constructor for Misere_X_O_Random_Player
template <typename T>
Misere_X_O_Random_Player<T>::Misere_X_O_Random_Player(string n,T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = n;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void Misere_X_O_Random_Player<T>::getmove(int& x, int& y) {
    // Random number between 0 and 2
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

// --------------------------------------------------------------------------

void Misere_X_O_rules() {
    cout << "Welcome to Misere Tic Tac Toe :)\n";
    cout << "Misere Tic Tac Toe, also known as Inverse Tic Tac Toe or Toe Tac Tic, is a unique twist on the classic game.\n";
    cout << "In this version, the objective is to avoid getting three marks in a row. The game flips the traditional\n";
    cout << "win condition on its head, making every move a strategic decision to prevent losing.\n";
    cout << "Rules:\n";
    cout << "The game is played on a standard 3x3 Tic-Tac-Toe grid. The goal is to avoid placing three of your marks\n";
    cout << "in a row, column, or diagonal. The player who ends up with three marks in a row loses the game.\n";
    cout << "If all cells are filled without either player aligning three marks in a row, the game ends in a draw.\n";
    cout << "Good Luck!\n\n\n";
}
void Misere_X_O_Gameplay() {
    int choice;
    Player<char>* players[2];
    Misere_X_O_Board <char>* B = new Misere_X_O_Board <char>();
    string playerXName, player2Name;
    // Set up player 1
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Player 1 name: ";
    getline(cin, playerXName);
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    cin >> choice;
    while (cin.fail() || (choice != 1 && choice != 2)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please choose 1 or 2.\n\n";
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice: ";
        cin >> choice;
    }
    char p1, p2;
    int choice2;
    cout << "1. 'X'\n";
    cout << "2. 'O'\n";
    cout << "Choose your symbol:";
    cin >> choice2;
    while (cin.fail() || (choice2 != 1 && choice2 != 2)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please choose 1 or 2.\n\n";
        cout << "1. 'X'\n";
        cout << "2. 'O'\n";
        cout << "Choose your symbol:";
        cin >> choice2;
    }
    if (choice2 == 1) {
        p1 = 'X';
        p2 = 'O';
    }
    else if (choice2 == 2) {
        p1 = 'O';
        p2 = 'X';
    }

    if (choice == 1) {
        players[0] = new Misere_X_O_Player<char>(playerXName, p1);
    }
    else if (choice == 2) {
        players[0] = new Misere_X_O_Random_Player<char>(playerXName,p1);
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, player2Name);
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    int choice3;
    cin >> choice3;
    while (cin.fail() || (choice3 != 1 && choice3 != 2)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please choose 1 or 2.\n\n";
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice: ";
        cin >> choice3;
    }
    if (choice3 == 1) {
        players[1] = new Misere_X_O_Player<char>(player2Name, p2);
    }
    else if (choice3 == 2) {
        players[1] = new Misere_X_O_Random_Player<char>(player2Name,p2);
    }
    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}
#endif
