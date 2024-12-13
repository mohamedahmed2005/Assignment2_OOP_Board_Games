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
    X_O_5x5_Random_Player(string n,T symbol);
    void getmove(int& x, int& y);
};



//--------------------------------------- IMPLEMENTATION 

#include <iostream>
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

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
        this->board[x][y] = toupper(mark);
        this->n_moves++;
        valid_moves = this->n_moves;
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void X_O_5x5_Board<T>::display_board() {
    if (this->n_moves == 25) {
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
    }
    if (this->n_moves == 24) {
        cout << "Player 1 score: " << player1_score << "\nPlayer 2 score: " << player2_score << "\n";
    }
    if (this->n_moves == 24 && player2_score > player1_score) {
        
        return true;
    }
    if (this->n_moves == 25 && player1_score > player2_score) {
        
            return true;
        
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
        cout << "\nGame rules: the cell you choose must be empty\n";
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
        if (x < 0 || x  > 4 || y < 0 || y > 4) {
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
X_O_5x5_Random_Player<T>::X_O_5x5_Random_Player(string n,T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = n ;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void X_O_5x5_Random_Player<T>::getmove(int& x, int& y) {
    
     // Random number between 0 and 4
      x = rand() % this->dimension;  
       y = rand() % this->dimension;
}

//------------------------------------------------------------------------------------------
void X_O_5x5_rules() {
    cout << "Welcome to 5x5 Tic Tac Toe :)\n";
    cout << "This tic-tac-toe variation is played on a 5 x 5 grid. As in the traditional game, players are Xs or Os.\n";
    cout << "Rules:\n";
    cout << "Players take turns placing an X or an O in one of the squares until all the squares except one are filled. (Each player has 12 turns for a total of 24 squares).\n";
    cout << "Winning:\n";
    cout << "Count the number of three-in-a-rows each player has. Sequences can be vertically, horizontally, or diagonally.\n";
    cout << "Whoever has the most, wins.\n";
    cout << "One mark be counted in more than one three-in-a-row sequence.\n";
    cout << "Good Luck!\n\n\n";
}
void X_O_5x5_Gameplay() {
    X_O_5x5_rules();
    int choice;
    Player<char>* players[2];
    X_O_5x5_Board <char>* B = new X_O_5x5_Board <char>();
    string playerXName, player2Name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Set up player 1
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
        players[0] = new X_O_5x5_Player<char>(playerXName, p1);
    }
    else if (choice == 2) {
        players[0] = new X_O_5x5_Random_Player<char>(playerXName,p1);
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
        players[1] = new X_O_5x5_Player<char>(player2Name, p2);
    }
    else if (choice3 == 2) {
        players[1] = new X_O_5x5_Random_Player<char>(player2Name,p2);
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
