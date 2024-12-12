#include"BoardGame_Classes.h"
#include<iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include<limits>
#include<map>
using namespace std;

vector<int> odd_numbers = {1, 3, 5, 7, 9};
vector<int> even_numbers={2,4,6,8};

map<int, pair<int, int>> moves;
template<typename T>
class Numerical_Tic_Tac_Toe_Board:public BoardGame_Classes<T> {
public:
    Numerical_Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
template<typename T>
Numerical_Tic_Tac_Toe_Board<T>::Numerical_Tic_Tac_Toe_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}
template<typename T>
void Numerical_Tic_Tac_Toe_Board<T>::display_board() {
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
bool Numerical_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        return false;
    }
    this->board[x][y] = symbol;

    moves[this->n_moves] = make_pair(x, y);
    ++this->n_moves;
    return true;
}
template <typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_win() {
    // Helper lambda to check a triplet sum
    auto is_valid_sum = [&](T a, T b, T c) {
        return (a != 0 && b != 0 && c != 0 && (a + b + c == 15));
    };

    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        if (is_valid_sum(this->board[i][0], this->board[i][1], this->board[i][2]) || // Row check
            is_valid_sum(this->board[0][i], this->board[1][i], this->board[2][i])) { // Column check
            return true;
            }
    }

    // Check diagonals
    if (is_valid_sum(this->board[0][0], this->board[1][1], this->board[2][2]) || // Top-left to bottom-right
        is_valid_sum(this->board[0][2], this->board[1][1], this->board[2][0])) { // Top-right to bottom-left
        return true;
        }

    return false;
}

template<typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}
template<typename T>
bool Numerical_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//-------------------------------------------------------------------
template<typename T>
class Numerical_Tic_Tac_Toe_player:public Player<T> {
public:
    Numerical_Tic_Tac_Toe_player(string n, vector<T> nums);
    void getmove(int& x, int& y) override;
private:
    vector<T> available_numbers;
};
template<typename T>
Numerical_Tic_Tac_Toe_player<T>::Numerical_Tic_Tac_Toe_player(string nm, vector<T> nums):Player<T>(nm,1) {
    this->available_numbers = nums;
}
template<typename T>
void Numerical_Tic_Tac_Toe_player<T>::getmove(int &x, int &y) {
    cout << this->name << "'s turn:" << endl;

    // Show available numbers for the player to choose
    for (const auto& num : available_numbers) {
        cout << num << " ";
    }
    cout << endl;

    int num;
    cout << "Enter number: ";
    cin >> num;

    // Validate number input to ensure it's in available_numbers
    while (cin.fail() || find(available_numbers.begin(), available_numbers.end(), num) == available_numbers.end()) {
        cout << "Invalid number! Choose from: ";
        for (const auto& num : available_numbers) {
            cout << num << " ";
        }
        cout << endl;
        cout << "Enter number: ";
        cin >> num;
    }

    // Remove the number from the available list after use
    available_numbers.erase(find(available_numbers.begin(), available_numbers.end(), num));
    this->symbol = num;

    // Now the game loop to get a valid x, y position (this part will not reject based on the number)
    while (true) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;

        // Check if the input is valid and the position is unoccupied
        if (cin.fail() || x < 0 || x > 2 || y < 0 || y > 2 ||
            any_of(moves.begin(), moves.end(), [x, y](const pair<int, pair<int, int>>& move) {
                return move.second.first == x && move.second.second == y;
            })) {
            cout << "Invalid input. Please enter numbers between 0 and 2 for an unoccupied position." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
                break;
            }
    }

}

//------------------------------------------------------------------------------------------------------------
template<typename T>
class Random_Numerical_Tic_Tac_Toe: public RandomPlayer<T> {
public:
    Random_Numerical_Tic_Tac_Toe(string name,const vector<T>& nums);
    void getmove(int &x, int &y) override;
private:
    vector<T> available_numbers;
};
template<typename T>
Random_Numerical_Tic_Tac_Toe<T>::Random_Numerical_Tic_Tac_Toe(string name,const vector<T>& nums)
    : RandomPlayer<T>(0), available_numbers(nums) {
    this->name = name+"_Random Computer";
}
template<typename T>
void Random_Numerical_Tic_Tac_Toe<T>::getmove(int &x, int &y) {
    srand(time(NULL));
    cout << this->name << "'s turn:" << endl;

    // Choose a random number from available numbers
    int rand_idx = rand() % available_numbers.size();
    this->symbol = available_numbers[rand_idx];
    available_numbers.erase(available_numbers.begin() + rand_idx); // Remove used number

    // Generate a random valid move
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (any_of(moves.begin(), moves.end(), [x, y](const pair<int, pair<int, int>>& move) {
        return move.second.first == x && move.second.second == y;
    }));
}
//------------------------------------------------------------------------------------------------------------------
void instuctions() {
    cout<<"-------------------------------------------------------------------------"<<endl;
    cout<<"This is Numerical Tic Tac Toe Game"<<endl;
    cout<<"Instuctions for playing this Game:"<<endl;
    cout<<"Rules: Player 1 typically starts and uses odd numbers (1, 3, 5, 7, 9), while Player 2 uses even numbers (2, 4, 6, 8). Players alternate turns, placing one number in an empty cell on the board. Each number can only be used once."<<endl;
    cout<<"Winning: A player wins by placing three numbers in a row, column, or diagonal that add up to 15."<<endl;
}
//------------------------------------------------------------------------------------------------------------
int Numerical_menu() {
    string choice;
    Player<int>* players[2];
    BoardGame_Classes<int>* B = new Numerical_Tic_Tac_Toe_Board<int>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Numerical Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    do {
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
    }while (cin.fail()||(choice!="1"&&choice!="2"));

    if (choice ==  "1") {
        players[0] = new Numerical_Tic_Tac_Toe_player<int>(playerXName, odd_numbers);
        cout << "Player X (" << playerXName << ") is a Human.\n";
    }
    else if (choice == "2") {
        players[0] = new Random_Numerical_Tic_Tac_Toe<int>(playerXName,odd_numbers); // Pass the vector
    }
    players[0]->setBoard(B);

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    do {
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
    }while (cin.fail()||(choice!="1"&&choice!="2"));

    if (choice=="1") {
        players[1] = new Numerical_Tic_Tac_Toe_player<int>(player2Name, even_numbers);
        cout << "Player 2 (" << player2Name << ") is a Human.\n";
    }
    if (choice=="2") {
        players[1] = new Random_Numerical_Tic_Tac_Toe<int>(player2Name,even_numbers); // Pass the vector
    }
    players[1]->setBoard(B);

    // Create the game manager and run the game
    GameManager<int> Numerical_Tic_Tac_Toe(B, players);
    instuctions();
    Numerical_Tic_Tac_Toe.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    moves.clear();
    return 0;
}
