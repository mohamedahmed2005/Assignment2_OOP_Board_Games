#include <iostream>
#include <map>
#include <utility>
using namespace std;

class Board {
public:
    Board(int rows, int cols) : rows(rows), cols(cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                board[{i, j}] = ' ';
            }
        }
    }
    void displayBoard() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << board[{i, j}];
                if (j < cols - 1) cout << " | ";
            }
            cout << endl;
            if (i < rows - 1) {
                cout << "===";
                for (int j = 1; j < cols; ++j) {
                    cout << " ===";
                }
                cout << endl;
            }
        }
    }
    bool updateBoard(int x, int y, char symbol) {
        if (x >= 0 && x < rows && y >= 0 && y < cols && board[{x, y}] == ' ') {
            board[{x, y}] = symbol;
            return true;
        }
        return false;
    }
    virtual bool isWin() = 0;
    virtual bool isDraw() = 0;

protected:
    int rows, cols;
    map<pair<int, int>, char> board;
};
class Player {
public:
    Player(string name, char symbol) : playerName(move(name)), playerSymbol(symbol) {}
    string getName() const { return playerName; }
    char getSymbol() const { return playerSymbol; }
private:
    string playerName;
    char playerSymbol;
};