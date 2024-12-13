#ifndef X_O_4X4_H
#define X_O_4X4_H

#include "BoardGame_Classes.h"


template <typename T>
class X_O_4x4_Board :public Board<T> {
public:
    X_O_4x4_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool valid_move(int x, int y, T symbol);
};


template <typename T>
class X_O_4x4_Player : public Player<T> {
public:
    X_O_4x4_Player(string name, T symbol);
    void getmove(int& x, int& y);

};


template <typename T>
class X_O_4x4_Random_Player : public RandomPlayer<T> {
public:
    X_O_4x4_Random_Player(string n,T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION 

#include <iostream>
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>


int oldX_pos = 0;
int oldy_pos = 0;
//   X_O_5x5_Board IMPLEMENTATION

template <typename T>
X_O_4x4_Board<T>::X_O_4x4_Board() {
    this->rows = this->columns = 4;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if (i == 0) {
                if (j % 2 == 0) {
                    this->board[i][j] = 'O';
                
                }else {
                    this->board[i][j] = 'X';

                }
            }
            else if (i == this->columns - 1) {
                if (j % 2 == 0) {
                    this->board[i][j] = 'X';

                }
                else {
                    this->board[i][j] = 'O';

                }

            }
            else {
                this->board[i][j] = ' ';
            }
        }
    }
    this->n_moves = 0;
}

// check if the move is valid and form any direction
template <typename T>
bool X_O_4x4_Board<T>::valid_move(int x, int y, T symbol) {
    if (this->board[x][y] == ' ') {
        int up = max(0, x - 1);
        int down = min(this->rows - 1, x + 1);
        int right = min(this->columns - 1, y + 1);
        int left = max(0, y - 1);
        if (up != x && this->board[up][y] == symbol) {
            return true; 
        }
        else if (down != x && this->board[down][y] == symbol) {
            return true;
        }
        else if (right != y && this->board[x][right] == symbol) {
            return true;
        }
        else if (left != y && this->board[x][left] == symbol) {
            return true;
        }
        else {
            return false; // move is NOT valid
        }
    }
    return false; // move is NOT valid
}

template <typename T>
bool X_O_4x4_Board<T>::update_board(int x, int y, T symbol) {
    if (this->board[oldX_pos][oldy_pos] != toupper(symbol)) {
        return false;
    }
    // Check if the move is to an adjacent cell (horizontally or vertically)
    if ((abs(oldX_pos - x) == 1 && oldy_pos == y) || (abs(oldy_pos - y) == 1 && oldX_pos == x)) {
        // Check if the target cell is empty
        if (this->board[x][y] == ' ') {
            this->board[oldX_pos][oldy_pos] = ' ';
            this->board[x][y] = toupper(symbol);
            this->n_moves++;
            return true;
        }
    }
    return false;
    
}

// Display the board and the pieces on it
template <typename T>
void X_O_4x4_Board<T>::display_board() {
    cout << "\n   ";
    for (int j = 0; j < this->columns; ++j) {
        cout << "   " << j << "   "; // Column headers with extra spacing
    }
    cout << "\n   " << string(this->columns * 8 + 1, '-') << "\n";

    for (int i = 0; i < this->rows; ++i) {
        cout << i << " |"; // Row header
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == ' ') {
                if (this->n_moves % 2 == 0 && valid_move(i, j, 'X')) {
                    cout << " (" << i << "," << j << ") |";
                }
                else if (this->n_moves % 2 == 1 && valid_move(i, j, 'O')) {
                    cout << " (" << i << "," << j << ") |";
                }
                else {
                    cout << "   " << this->board[i][j] << "   |";
                }
                
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
bool X_O_4x4_Board<T>::is_win() {
    // Check rows for three in a row
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            if (this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2] &&
                this->board[i][j] != ' ') {
                return true;
            }
        }
    }

    // Check columns for three in a row
    for (int j = 0; j < this->columns; ++j) {
        for (int i = 0; i <= this->rows - 3; ++i) {
            if (this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j] &&
                this->board[i][j] != ' ') {
                return true;
            }
        }
    }

    // Check top-left to bottom-right diagonals for three in a row
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 0; j <= this->columns - 3; ++j) {
            if (this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2] &&
                this->board[i][j] != ' ') {
                return true;
            }
        }
    }

    // Check top-right to bottom-left diagonals for three in a row
    for (int i = 0; i <= this->rows - 3; ++i) {
        for (int j = 2; j < this->columns; ++j) {
            if (this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2] &&
                this->board[i][j] != ' ') {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool X_O_4x4_Board<T>::is_draw() {

    return false; // there's NO draw in this game according to its rules
}
template <typename T>
bool X_O_4x4_Board<T>::game_is_over() {
    return is_win();
}

//--------------------------------------
//   X_O_5x5_Player IMPLEMENTATION
// Constructor for X_O_4x4_Player
template <typename T>
X_O_4x4_Player<T>::X_O_4x4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_4x4_Player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << this->getname() << " turn. Your symbol is " << this->getsymbol();
        cout << "\nPlease enter the position that you to move from a and b (0 to 3) separated by spaces: ";
        if (!(cin >> oldX_pos >> oldy_pos)) {
            // Clear error flag
            cin.clear();

            // Discard invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter two integers.\n";
            continue;
        }
        if (oldX_pos < 0 || oldX_pos  > 3 || oldy_pos < 0 || oldy_pos > 3) {
            cout << "Invalid move. Coordinates must be between 0 and 3.\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "\nGame rules: the cell you choose must be empty and Tokens can be moved horizontally or vertically but not diagonally \n";
        cout << this->getname() << " turn. Your symbol is " << this->getsymbol();
        cout << "\nPlease enter your move x and y (0 to 3) separated by spaces in one of the avaliable cells: ";
        // Check if input is valid
        if (!(cin >> x >> y)) {
            // Clear error flag
            cin.clear();

            // Discard invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter two integers.\n";
            continue;
        }
        if (x < 0 || x  > 3 || y < 0 || y > 3) {
            cout << "Invalid move. Coordinates must be between 0 and 3.\n";
            continue;
        }
        break;
    }
    
}

//--------------------------------------
//   X_O_5x5_Random_Player IMPLEMENTATION

// Constructor for X_O_4x4_Random_Player
template <typename T>
X_O_4x4_Random_Player<T>::X_O_4x4_Random_Player(string n,T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = n;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void X_O_4x4_Random_Player<T>::getmove(int& x, int& y) {

    // Random number between 0 and 3
    oldX_pos = rand() % this->dimension;
    oldy_pos = rand() % this->dimension;
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    
}

// -----------------------------------------------------------------------------------------------------

void X_O_4x4_rules() {
    cout << "Welcome to 4x4 Tic Tac Toe :)\n";
    cout << "4 x 4 Tic-Tac-Toe is an extended version of the classic game, played on a larger board with more\n";
    cout << "complex strategies. Each player has four tokens and aims to align three tokens in a row to win. This\n";
    cout << "game introduces new movement rules and strategic depth to the traditional Tic-Tac-Toe. The game is\n";
    cout << "played on a 4x4 grid. Each player has four tokens. Tokens are placed in specific starting positions:\n";
    cout << "two tokens on opposite sides of the board for each player. (as shown in the image).\n";
    cout << "Rules:\n";
    cout << "Players alternate turns, moving one of their tokens to an immediately adjacent open square.\n";
    cout << "Tokens can be moved horizontally or vertically but not diagonally. Tokens may not jump over other\n";
    cout << "tokens. The goal is to align three of your tokens in a row. This can be achieved horizontally, vertically, or diagonally.\n";
    cout << "Winning:\n";
    cout << "The first player to get three tokens in a row wins the game. The alignment can be in any direction: horizontal, vertical, or diagonal.\n";
    cout << "Good Luck!\n\n\n";
}

void X_O_4x4_Gameplay() {
    X_O_4x4_rules();
    int choice;
    Player<char>* players[2];
    X_O_4x4_Board <char>* B = new X_O_4x4_Board <char>();
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
   
    if (choice == 1) {
        players[0] = new X_O_4x4_Player<char>(playerXName, 'X');
    }
    else if (choice == 2) {
        players[0] = new X_O_4x4_Random_Player<char>(playerXName, 'X');
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
        players[1] = new X_O_4x4_Player<char>(player2Name, 'O');
    }
    else if (choice3 == 2) {
        players[1] = new X_O_4x4_Random_Player<char>(player2Name, 'O');
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

