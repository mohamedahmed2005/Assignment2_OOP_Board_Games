//
// Created by VICTUS on 11/30/2024.
//

#ifndef GAME_5_H
#define GAME_5_H
#include"Board.h"
#include<iomanip>
#include<limits>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

inline vector<int> used_numbers;
inline vector<int> even_numbers = {2, 4, 6, 8};
inline vector<int> odd_numbers = {1, 3, 5, 7, 9};

template<typename T>
class Numerical_Tic_Tac_Toe:public Board<T> {
private:
    public:
    Numerical_Tic_Tac_Toe ();
    bool update_board (int x , int y , T symbol) override;
    void display_board () override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
template <typename T>
class Numerical_Tic_Tac_Toe_player : public Player<T> {
public:
    Numerical_Tic_Tac_Toe_player (string name, T symbol);
    void getmove(int& x, int& y) ;
    bool isempty(int& x,int&y);

};
template<typename T>
Numerical_Tic_Tac_Toe<T>::Numerical_Tic_Tac_Toe() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template <typename T>
void Numerical_Tic_Tac_Toe<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}
template<typename T>
bool Numerical_Tic_Tac_Toe<T>::update_board(int x, int y, T symbol) {
    if (!this->board) {
        return false;
    }
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        return false;
    }
    if (symbol == 0 || find(used_numbers.begin(), used_numbers.end(), symbol) != used_numbers.end()) {
        return false;
    }
    if (find(even_numbers.begin(), even_numbers.end(), symbol) != even_numbers.end()) {
        even_numbers.erase(remove(even_numbers.begin(), even_numbers.end(), symbol), even_numbers.end());
    } else if (find(odd_numbers.begin(), odd_numbers.end(), symbol) != odd_numbers.end()) {
        odd_numbers.erase(remove(odd_numbers.begin(), odd_numbers.end(), symbol), odd_numbers.end());
    } else {
        return false;
    }
    this->board[x][y] = symbol;
    used_numbers.push_back(symbol);
    ++this->n_moves;

    return true;
}

template <typename T>
bool Numerical_Tic_Tac_Toe<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) {
            return true;
        }
        if (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) {
            return true;
        }
    }
    if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) {
        return true;
    }
    if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15) {
        return true;
    }
    return false;
}
template <typename T>
bool Numerical_Tic_Tac_Toe<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}
template <typename T>
bool Numerical_Tic_Tac_Toe<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
Numerical_Tic_Tac_Toe_player<T>::Numerical_Tic_Tac_Toe_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Numerical_Tic_Tac_Toe_player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;

        // Check if input is valid
        if (cin.fail() || x < 0 || x > 2 || y < 0 || y > 2) {
            cout << "Invalid input. Please enter numbers between 0 and 2." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        } else {
            break; // Valid input and the spot is empty
        }
    }
}
template <typename T>
class Numerical_Game_manager : public GameManager<T> {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];
public:
    // Pass board and players to base class constructor
    Numerical_Game_manager(Board<T>* bPtr, Player<T>* playerPtr[2])
        : GameManager<T>(bPtr, playerPtr) {
        boardPtr = bPtr;
        players[0] = playerPtr[0];
        players[1] = playerPtr[1];
    }
    void run();
};

template <typename T>
void Numerical_Game_manager<T>::run() {
    int x, y, choice;

    boardPtr->display_board();

    while (!boardPtr->game_is_over()) {
        for (int i : {0, 1}) {
            cout << players[i]->getname() << "'s turn.\n";
            if (i == 0) {
                // Player 1 (Odd Numbers)
                cout << "Available odd numbers: ";
                for (int num : boardPtr->odd_numbers) {
                    cout << num << " ";
                }
                cout << "\nChoose a number: ";
                cin >> choice;

                while (find(boardPtr->odd_numbers.begin(), boardPtr->odd_numbers.end(), choice) == boardPtr->odd_numbers.end()) {
                    cout << "Invalid choice. Choose from the available odd numbers: ";
                    cin >> choice;
                }
                boardPtr->odd_numbers.erase(remove(boardPtr->odd_numbers.begin(), boardPtr->odd_numbers.end(), choice), boardPtr->odd_numbers.end());
            } else {
                // Player 2 (Even Numbers)
                cout << "Available even numbers: ";
                for (int num : boardPtr->even_numbers) {
                    cout << num << " ";
                }
                cout << "\nChoose a number: ";
                cin >> choice;

                while (find(boardPtr->even_numbers.begin(), boardPtr->even_numbers.end(), choice) == boardPtr->even_numbers.end()) {
                    cout << "Invalid choice. Choose from the available even numbers: ";
                    cin >> choice;
                }
            }
            boardPtr->even_numbers.erase(remove(boardPtr->even_numbers.begin(), boardPtr->even_numbers.end(), choice), boardPtr->even_numbers.end());
            players[i]->getmove(x, y);

            while (!boardPtr->update_board(x, y, choice)) {
                cout << "Invalid move. Try again.\n";
                players[i]->getmove(x, y);
            }

            boardPtr->display_board();

            if (boardPtr->is_win()) {
                cout << players[i]->getname() << " wins!\n";
                return;
            }
            if (boardPtr->is_draw()) {
                cout << "It's a draw!\n";
                return;
            }
        }
    }
}

#endif //GAME_5_H
