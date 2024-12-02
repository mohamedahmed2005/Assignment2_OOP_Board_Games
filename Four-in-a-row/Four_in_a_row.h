#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"

template <typename T>
class ConnectFourBoard : public BoardGame_Classes<T> {
public:
    ConnectFourBoard() {
        this->rows = 6;
        this->columns = 7;
        this->board = new T*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns];
            std::fill(this->board[i], this->board[i] + this->columns, '.'); // Fill with empty symbol
        }
    }

    ~ConnectFourBoard() {
        for (int i = 0; i < this->rows; ++i) {
            delete[] this->board[i];
        }
        delete[] this->board;
    }

    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= this->columns || this->board[0][x] != '.') {
            return false; // Invalid move
        }
        // Place symbol in the lowest available row
        for (int i = this->rows - 1; i >= 0; --i) {
            if (this->board[i][x] == '.') {
                this->board[i][x] = symbol;
                this->n_moves++;
                return true;
            }
        }
        return false; // Should never reach here if the move is valid
    }

    void display_board() override {
        // Print the board with square alignment
        for (int i = 0; i < this->rows; i++) {
            cout << string(this->columns * 4 + 1, '-') << "\n|"; // Row separator
            for (int j = 0; j < this->columns; j++) {
                cout << " " << (this->board[i][j] ? this->board[i][j] : '.') << " |";
            }
            cout << endl;
        }
        // Bottom border
        cout << string(this->columns * 4 + 1, '-') << endl;

        // Print column numbers
        for (int i = 0; i < this->columns; i++) {
            cout << "  " << i << " "; // Align column numbers
        }
        cout << endl;
    }



    bool is_win() override {
        // Check horizontal, vertical, and diagonal for a win
        return check_horizontal() || check_vertical() || check_diagonal();
    }

    bool is_draw() override {
        return this->n_moves >= this->rows * this->columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }

private:
    bool check_horizontal() {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (this->board[i][j] != '.' &&
                    this->board[i][j] == this->board[i][j + 1] &&
                    this->board[i][j] == this->board[i][j + 2] &&
                    this->board[i][j] == this->board[i][j + 3]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool check_vertical() {
        for (int j = 0; j < this->columns; ++j) {
            for (int i = 0; i <= this->rows - 4; ++i) {
                if (this->board[i][j] != '.' &&
                    this->board[i][j] == this->board[i + 1][j] &&
                    this->board[i][j] == this->board[i + 2][j] &&
                    this->board[i][j] == this->board[i + 3][j]) {
                    return true;
                }
            }
        }
        return false;
    }

    bool check_diagonal() {
        // Check for diagonals from bottom-left to top-right
        for (int i = 3; i < this->rows; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (this->board[i][j] != '.' &&
                    this->board[i][j] == this->board[i - 1][j + 1] &&
                    this->board[i][j] == this->board[i - 2][j + 2] &&
                    this->board[i][j] == this->board[i - 3][j + 3]) {
                    return true;
                }
            }
        }
        // Check for diagonals from top-left to bottom-right
        for (int i = 0; i <= this->rows - 4; ++i) {
            for (int j = 0; j <= this->columns - 4; ++j) {
                if (this->board[i][j] != '.' &&
                    this->board[i][j] == this->board[i + 1][j + 1] &&
                    this->board[i][j] == this->board[i + 2][j + 2] &&
                    this->board[i][j] == this->board[i + 3][j + 3]) {
                    return true;
                }
            }
        }
        return false;
    }
};

template <typename T>
class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << this->getname() << ", enter column (0-6): ";
        cin >> x;
        y = 0; // y is not used in this game
    }
};
int menu() {
    ConnectFourBoard<char> board;
    Player<char>* players[2];
    players[0] = new HumanPlayer<char>("Mohamed", 'X');
    players[1] = new HumanPlayer<char>("Salma",'O');

    GameManager<char> gameManager(&board, players);
    gameManager.run();

    delete players[0];
    delete players[1];
    return 0;
}