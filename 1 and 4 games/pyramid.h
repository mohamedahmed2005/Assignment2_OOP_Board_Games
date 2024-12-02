#ifndef A2_T2_P1_4_PYRAMID_H
#define A2_T2_P1_4_PYRAMID_H

#include <iostream>
#include <vector>
#include "BoardGame_Classes.h"

using namespace std;



/// --------------------------------------------------------------------------------- Pyramid board class

template <typename T>
class PyramidBoard : public Board<T> {
private:

    bool is_within_bounds(int x, int y);  // Check if a position is within bounds
    bool check_line(int x, int y, T symbol);  // Check line for win condition

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
bool PyramidBoard<T>::check_line(int x, int y, T symbol) {
    // Check horizontal line
    if (y - 2 >= 0 && this->board[x][y - 2] == symbol && this->board[x][y - 1] == symbol && this->board[x][y] == symbol) {
        return true;
    }

    // Check diagonal lines (both directions)
    if (x + 2 < this->rows && y - 2 >= 0 &&
        this->board[x + 1][y - 1] == symbol && this->board[x + 2][y - 2] == symbol) {
        return true;
    }

    if (x + 2 < this->rows && y + 2 < 2 * (x + 2) + 1 &&
        this->board[x + 1][y + 1] == symbol && this->board[x + 2][y + 2] == symbol) {
        return true;
    }

    if (x + 2 < this->rows && y - 2 >= 0 &&
        this->board[x + 1][y + 2] == symbol && this->board[x + 2][y + 3] == symbol) {
        return true;
    }
    return false;
}

template <typename T>
bool PyramidBoard<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        // Loop through each element in the current row
        for (int j = 0; j < 2 * i + 1; ++j) {
            // Only check if the symbol is not '-'
            if (this->board[i][j] != '-') {
                // Check for a winning line starting from (i, j)
                if (check_line(i, j, this->board[i][j])) {
                    return true;  // A win is detected
                }
            }
        }
    }
    return false;  // No win detected
}



// Update the board
template <typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (!is_within_bounds(x, y) || this->board[x][y] != '-') {
        cout << "Invalid move. Try again.\n";
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
public:
    PyramidPlayer(string n, T symbol) ;
    void getmove(int& x, int& y) override;
};





template <typename T>
PyramidPlayer<T>::PyramidPlayer(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
void PyramidPlayer<T>::getmove(int& x, int& y) {
    // Implementation for getting the move (can be extended)
    cout << "Enter the row\n";
    cin >> x;
    cout << "Enter the column\n";
    cin >> y;
}


/// ----------------------------------------------------------------------------------  Random player Pyramid class

template <typename T>
class PyramidRandomPlayer : public RandomPlayer<T> {
public:
    PyramidRandomPlayer(T symbol);

    // Generates a random move for the pyramid board.
    void getmove(int& x, int& y);
};

template <typename T>
PyramidRandomPlayer<T>::PyramidRandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Mr. Habida";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void PyramidRandomPlayer<T>::getmove(int& x, int& y) {
    x = rand() % 2;
    y = rand() % 4;
}


/// ---------------------------------------------------------------- AI_Min_Max Pyramid player











/// ---------------------------------------------------------------- Implementation Function
void PyramidGame(){
    string choice;
    Player<char>* players[2];
    Board<char>* pyramid_board = new PyramidBoard<char>();
    string player1Name, player2Name;
    char s1,s2;
    cout << "Welcome to my Pyramid X-O Game.\n";

    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    do {
        cout << "Please choose your symbol\n" << "1. to select 'X'\n" << "2. to select 'O'\n";
        cin >> choice;
        if(choice == "1"){
            s1 = 'X';
            s2 = 'O';
            break;
        }else if(choice == "2"){
            s1 = 'O';
            s2 = 'X';
            break;
        }else{
            cout << "Invalid choice. Please try again.\n";
        }
    }while (true);
    players[0] = new PyramidPlayer<char>(player1Name, s1);

    // Ensure Player 2 has a unique name
    while (player2Name == player1Name) {
        cout << "Player 2 name cannot be the same as Player 1. Enter a different name: ";
        cin >> player2Name;
    }

    do {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
        if (choice == "1") {
            // Set up Player 2
            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            players[1] = new PyramidPlayer<char>(player2Name, s2);
            break;
        }else if(choice == "2") {
            players[1] = new PyramidRandomPlayer<char>(s2);
            break;
        }else {
            cout << "Invalid choice for Player 2. Please try again.\n";
        }
    }while (true);


    // Assign board to players
    players[0]->setBoard(pyramid_board);
    players[1]->setBoard(pyramid_board);
    cout << "(" << players[0]->getname() << "( with symbol " << players[0]->getsymbol() << " _vs_ ("
         << players[1]->getname() << ") with symbol " << players[1]->getsymbol() << endl;

    // Run the game
    GameManager<char> pyramidGame(pyramid_board, players);
    pyramidGame.run();

    // Clean up
    delete players[0];
    delete players[1];
    delete pyramid_board;

    return;
}
#endif