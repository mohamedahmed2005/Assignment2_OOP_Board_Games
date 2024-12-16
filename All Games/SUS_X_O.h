#ifndef _SUS_X_O_H
#define _SUS_X_O_H

#include "BoardGame_Classes.h"
#include <vector>

template <typename T>
class SUS_X_O_Board :public Board<T> {
private:
    vector<bool> visited_path;
    int Player1_Score;
    int Player2_Score;
public:
	SUS_X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class SUS_X_O_Player : public Player<T> {
public:
    SUS_X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);

};

template <typename T>
class SUS_X_O_Random_Player : public RandomPlayer<T> {
public:
    SUS_X_O_Random_Player(string n, T symbol);
    void getmove(int& x, int& y);
};

//--------------------------------------- IMPLEMENTATION 

#include <iostream>
#include <string>
#include <iomanip>
#include <iostream>
#include <iomanip>
#include <cctype>
bool Vs_computer = false;
int moves_counter = 0;
int human_turn_vs_computer = 0;

// SUS_X_O_Board IMPLEMENTATION
template <typename T>
SUS_X_O_Board<T> ::SUS_X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
    this->Player1_Score = 0;
    this->Player2_Score = 0;
    this->visited_path.resize(8, false);
}

template <typename T>
bool SUS_X_O_Board<T>::update_board(int x, int y, T mark) {
    // make a fake move to check if player 2 is the winner
    if (this->n_moves == 9) {
        this->n_moves++;
        return true;
    }
    // Only update if move is valid
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ') {
        this->n_moves++;
        moves_counter = this->n_moves;
        char symbol;
        if (!Vs_computer) {
            int choice;
            cout << "1. 'S'\n";
            cout << "2. 'U'\n";
            cout << "Choose the symbol you want to put in this cell:";
            cin >> choice;
            while (cin.fail() || (choice != 1 && choice != 2)) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please choose 1 or 2.\n\n";
                cout << "1. 'S'\n";
                cout << "2. 'U'\n";
                cout << "Choose the symbol you want to put in this cell:";
                cin >> choice;
            }
            (choice == 1 ? symbol = 'S' : symbol = 'U');
        }
        else if (Vs_computer) {
            if ((human_turn_vs_computer == 1 && this->n_moves % 2 == 1) ||
                (human_turn_vs_computer == 2 && this->n_moves % 2 == 0)) {
                int choice1;
                cout << "1. 'S'\n";
                cout << "2. 'U'\n";
                cout << "Choose the symbol you want to put in this cell:";
                cin >> choice1;
                while (cin.fail() || (choice1 != 1 && choice1 != 2)) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please choose 1 or 2.\n\n";
                    cout << "1. 'S'\n";
                    cout << "2. 'U'\n";
                    cout << "Choose the symbol you want to put in this cell:";
                    cin >> choice1;
                }
                (choice1 == 1 ? symbol = 'S' : symbol = 'U');
            }
            else {
                int random = rand() % 2;
                (random == 0 ? symbol = 'S' : symbol = 'U');
            }
        }
        this->board[x][y] = toupper(symbol);
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void SUS_X_O_Board<T> :: display_board() {
    if (this->n_moves == 10) {
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
bool SUS_X_O_Board<T> :: is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S')) {
            if (this->visited_path[i] == false) {
                (this->n_moves % 2 == 1 ? this->Player1_Score++ : this->Player2_Score++);
                this->visited_path[i] = true;
            }
            
        }
    }
    for (int j = 0; j < this->columns; j++) {
        if ((this->board[0][j] == 'S' && this->board[1][j] == 'U' && this->board[2][j] == 'S')) {
            if (this->visited_path[j + 3] == false) {
                (this->n_moves % 2 == 1 ? this->Player1_Score++ : this->Player2_Score++);
                this->visited_path[j + 3] = true;
            }
        }
    }
    // Check diagonals
    if ((this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S')) {
        if (this->visited_path[6] == false) {
            (this->n_moves % 2 == 1 ? this->Player1_Score++ : this->Player2_Score++);
            this->visited_path[6] = true;
        }
    }
    if ((this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S')) {
        if (this->visited_path[7] == false) {
            (this->n_moves % 2 == 1 ? this->Player1_Score++ : this->Player2_Score++);
            this->visited_path[7] = true;
        }
    }
    if (this->n_moves == 9) {
        cout << "Player 1 score: " << this->Player1_Score << "\nPlayer 2 score: " << this->Player2_Score << "\n";
    }
    if (this->n_moves == 9 && this->Player1_Score > this->Player2_Score) {
        Vs_computer = false;
        moves_counter = 0;
        human_turn_vs_computer = 0;
        return true;
    }
    if (this->n_moves == 10 && this->Player1_Score < this->Player2_Score) {
        Vs_computer = false;
        moves_counter = 0;
        human_turn_vs_computer = 0;
        return true;
    }
    return false;
}

template <typename T>
bool SUS_X_O_Board<T> :: is_draw() {
    if (this->n_moves == 10 && !is_win()) {
        Vs_computer = false;
        moves_counter = 0;
        human_turn_vs_computer = 0;
        return true;
    }
    return false;
}
template <typename T>
bool SUS_X_O_Board<T> ::game_is_over() {
    return (this->n_moves == 10);
}

//--------------------------------------
//   SUS_X_O_Player IMPLEMENTATION

// Constructor for SUS_X_O_Player
template <typename T>
SUS_X_O_Player<T>::SUS_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
void SUS_X_O_Player<T>::getmove(int& x, int& y) {
    if (moves_counter == 9) {
        return;
    }
    while (true) {
        cout << "\nThe cell you choose must be empty\n";
        cout << this->getname() << " turn.";
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
    return;
}
//--------------------------------------
//   SUS_X_O_Random_Player IMPLEMENTATION

// Constructor for SUS_X_O_Random_Player
template <typename T>
SUS_X_O_Random_Player<T>::SUS_X_O_Random_Player(string n, T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = n;
    Vs_computer = true;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}
template <typename T>
void SUS_X_O_Random_Player<T>::getmove(int& x, int& y) {
    // Random number between 0 and 2
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

//------------------------------------------------------------------------------------------

void SUS_game_rules() {
    cout << "Welcome to the SUS Game! :)\n";
    cout << "The SUS game is a simple game played on a 3x3 grid.\n";
    cout << "The objective is to form the sequence \"S-U-S\" by placing letters in the grid.\n";
    cout << "Players must carefully plan their moves to create as many SUS sequences as possible\n";
    cout << "while blocking their opponent from doing the same.\n\n";

    cout << "Rules:\n";
    cout << "The goal is to create the sequence \"S-U-S\" in a straight line, which can be\n";
    cout << "achieved diagonally, horizontally, or vertically.\n";
    cout << "Players take turns placing either an \"S\" or a \"U\" in any empty square on the grid.\n";
    cout << "If a player successfully creates an \"S-U-S\" sequence, they take a point.\n\n";

    cout << "Winning:\n";
    cout << "The game continues until all squares are filled or no more \"S-U-S\" sequences\n";
    cout << "can be created. The player who creates the most \"S-U-S\" sequences wins the game.\n";
    cout << "Good Luck!\n\n\n";
}

void SUS_Gameplay() {
    SUS_game_rules();
    int choice;
    Player<char>* players[2];
    SUS_X_O_Board <char>* B = new SUS_X_O_Board <char>();
    string playerXName, player2Name;
    // Set up player 1
    cin.clear();
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
        players[0] = new SUS_X_O_Player<char>(playerXName, 'S');
        human_turn_vs_computer = 1;
    }
    else if (choice == 2) {
        players[0] = new SUS_X_O_Random_Player<char>(playerXName, 'U');
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, player2Name);
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "Enter your choice: ";
    int choice2;
    cin >> choice2;
    while (cin.fail() || (choice2 != 1 && choice2 != 2)) {
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please choose 1 or 2.\n\n";
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice: ";
        cin >> choice2;
    }
    if (choice2 == 1) {
        players[1] = new SUS_X_O_Player<char>(player2Name, 'S');
        human_turn_vs_computer = 2;
    }
    else if (choice2 == 2) {
        players[1] = new SUS_X_O_Random_Player<char>(player2Name, 'U');
    }
    if (choice == 1 && choice2 == 1) {
        human_turn_vs_computer = 0;
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
