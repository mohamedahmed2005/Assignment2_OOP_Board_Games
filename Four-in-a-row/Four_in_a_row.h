#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
using namespace std;
template <typename T>
class Four_in_a_row_Board : public BoardGame_Classes<T> {
public:
    Four_in_a_row_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
//--------------------------------------------------------------
template <typename T>
class Four_in_a_row_player : public Player<T> {
public:
    Four_in_a_row_player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override;
};
//----------------------------------------------------------------------------
template <typename T>
class Random_Four_in_a_row:public RandomPlayer<T> {
public:
    Random_Four_in_a_row(T symbol) : RandomPlayer<T>(symbol) {}
    void getmove(int& x, int& y) override;
};
//----------------------------------------------------------------
template<typename T>
Four_in_a_row_Board<T>::Four_in_a_row_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        fill(this->board[i], this->board[i] + this->columns, '.');
    }
}
template<typename T>
void Four_in_a_row_Board<T>::display_board() {
    // Print the board with square alignment
    for (int i = 0; i < this->rows; i++) {
        cout << string(this->columns * 4 + 1, '-') << "\n|";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << (this->board[i][j] ? this->board[i][j] : '.') << " |";
        }
        cout << endl;
    }
    cout << string(this->columns * 4 + 1, '-') << endl;

    for (int i = 0; i < this->columns; i++) {
        cout << "  " << i << " ";
    }
    cout << endl;
}
template<typename T>
bool Four_in_a_row_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->columns || this->board[0][x] != '.') {
        return false; // Invalid move
    }
    for (int i = this->rows - 1; i >= 0; --i) {
        if (this->board[i][x] == '.') {
            this->board[i][x] = symbol;
            ++this->n_moves;
            return true;
        }
    }
    return false;
}
template<typename T>
bool Four_in_a_row_Board<T>::is_win() {
    // check horizontal
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
    // check vertical
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
template<typename T>
bool Four_in_a_row_Board<T>::is_draw() {
    return this->n_moves >= 42 && !is_win();
}
template<typename T>
bool Four_in_a_row_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
//-----------------------------------------------------
template<typename T>
void Four_in_a_row_player<T>::getmove(int &x, int &y) {
    cout<<this->name<<"'s turn";
    cout<<"Please enter column between (0,6) : ";
    cin>>x;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout<<"Please enter column between (0,6) : ";
        cin>>x;
    }
    y = 0;
}
//----------------------------------------------------------
template<typename T>
void Random_Four_in_a_row<T>::getmove(int &x, int &y) {
    int last_x = -1;
    int last_y = -1;
    srand(time(NULL));
    cout << this->name << "'s turn" << endl;
    do {
        x = rand() % 6;
        y = 0;
    } while (x == last_x && y == last_y);
    last_x = x;
    last_y = y;
}
void instructions() {
    cout<<"-----------------------------------------"<<endl;
    cout<<"This is Connect Four Game"<<endl;
    cout<<"Instuctions for playing this Game:"<<endl;
    cout<<"Rules: The first player places an X or O in the bottom square of any column. Taking turns, players make their mark in any column, as long as it is in the lowest square possible."<<endl;
    cout<<"Winning: The first player to get four-in-a-row vertically, horizontally, or diagonally wins."<<endl;;
}
int Four_in_a_row_menu() {
    string choice;
    BoardGame_Classes<char>* B = new Four_in_a_row_Board<char>();
    Player<char>* players[2];
    string player1Name, player2Name;
    char x1 , x2;
    string choose;
    cout << "Welcome to FCAI Four in a row Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> player1Name;
    do {
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";
        cin >> choice;
    }while (cin.fail()||(choice!="1"&&choice!="2"&&choice!="3"));
    do {
        cout<<"Enter symbol that you want to play"<<endl;
        cout<<"1. X"<<endl;
        cout<<"2. O"<<endl;
        cin>>choose;
    } while (choose!="1"&&choose!="2");
    if (choose=="1") {
        x1 = 'X';
        x2 = 'O';
    }
    else if (choose=="2") {
        x1 = 'O';
        x2 = 'X';
    }
    if (choice == "1") {
        players[0] = new Four_in_a_row_player<char>(player1Name,x1);
        cout << "Player X (" << player1Name << ") is a Human.\n";
    }
    else if (choice == "2") {
        players[0] = new Random_Four_in_a_row<char>(x1);
    }
    players[0]->setBoard(B);

    // Set up player 2
    cout << "Enter Player Y name: ";
    cin >> player2Name;
    do {
        cout << "Choose Player Y type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. Smart Computer (AI)\n";
        cin >> choice;
    }while (cin.fail()||(choice!="1"&&choice!="2"&&choice!="3"));
    if (choice == "1") {
        players[1] = new Four_in_a_row_player<char>(player2Name,x2);
        cout << "Player Y (" << player2Name << ") is a Human.\n";
    }
    else if (choice == "2") {
        players[1] = new Random_Four_in_a_row<char>(x2);
    }
    players[0]->setBoard(B);
    GameManager<char> four_in_a_row(B, players);
    instructions();
    four_in_a_row.run();
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    return 0;
}
