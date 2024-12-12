//
// Created by Amr khaled on 12/12/2024.
//

#ifndef FINAL_BOAED_GAME_VERSION_WORD_TIC_TAC_TOE_H
#define FINAL_BOAED_GAME_VERSION_WORD_TIC_TAC_TOE_H
#include "Pyramid.h"
#include "BoardGame_Classes.h"
#include <memory>
#include <fstream>
#include <set>
#include <algorithm>

static int moves = 0;  // Keep track of the number of moves made

// Function to generate a random number within a range
#define BOARD_SIZE 3  // Pyramid has 3 levels
using namespace std;


template <typename T>
class Word_Tic_Tac_Toe_Board : public Board<T> {
private:

    set <string> words;
    bool is_within_bounds(int x, int y);  // Check if a position is within bounds
    bool check_line(int x, int y);  // Check line for win condition

public:

    Word_Tic_Tac_Toe_Board();  // Constructor
    ~Word_Tic_Tac_Toe_Board();  // Destructor to free dynamically allocated memory

    bool update_board(int x, int y, T symbol) override;  // Update the board with a symbol
    void display_board() override;  // Display the pyramid board
    bool is_win() override;  // Check if there is a winner
    bool is_draw() override;  // Check if the game is a draw
    bool game_is_over() override;  // Check if the game is over
};



// Constructor
template <typename T>
Word_Tic_Tac_Toe_Board<T>::Word_Tic_Tac_Toe_Board() {
    this->rows = 3;  // Pyramid has 3 levels
    this->columns = 3;  // Base row has 5 columns
    this->n_moves = 0;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[3];  // Each row has 2*i+1 columns
        for (int j = 0; j < 3; ++j) {
            this->board[i][j] = '-';  // Initialize all cells to '-'
        }
    }
    unique_ptr< ifstream> filePtr =  make_unique< ifstream>("dic.txt");

    if (!filePtr->is_open()) {
        cerr << "Error: Could not open the file 'dic.txt'." <<  endl;
        exit(505); // Exit with an error code if file can't be opened
    }

    string line;
    while ( getline(*filePtr, line)) {
        words.insert(line); // Insert each word from the file into the set
        string reversed_line = line;  // Copy the word
        reverse(reversed_line.begin(), reversed_line.end());  // Reverse the word
        words.insert(reversed_line);  //
    }

    // Optional: Show the words loaded from the file (for debugging)
//    cout << "Words loaded from 'dic.txt':" <<  endl;
//    for (const auto& word : words) {
//        cout << word <<  endl;
//    }
}



// Destructor
template <typename T>
Word_Tic_Tac_Toe_Board<T>::~Word_Tic_Tac_Toe_Board() {
    for (int i = 0; i < this->rows; ++i) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

// Check bounds
template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::is_within_bounds(int x, int y) {
    return x >= 0 && x < this->rows && y >= 0 && y < this->columns;
}

template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::check_line(int x, int y) {
//    filePtr->seekg(0,  ios::beg);

    for(string word : words){
        string board_line;
//        cout << word << endl;
        // Check horizontal lines
        for (int i = 0; i < this->rows; ++i) {
            board_line.clear();
            for (int j = 0; j < this->columns; ++j) {
                board_line += this->board[i][j];
            }
            if (board_line == word) return true;
        }

        // Check vertical lines
        for (int j = 0; j < this->columns; ++j) {
            board_line.clear();
            for (int i = 0; i < this->rows; ++i) {
                board_line += this->board[i][j];
            }
            if (board_line == word) return true;
        }

        // Check diagonals
        board_line.clear();
        for (int i = 0; i < this->rows; ++i) {
            board_line += this->board[i][i];  // Top-left to bottom-right
        }
        if (board_line == word) return true;

        board_line.clear();
        for (int i = 0; i < this->rows; ++i) {
            board_line += this->board[i][this->columns - i - 1];  // Top-right to bottom-left
        }
        if (board_line == word) return true;
    }
    return false;
}

// Check if there's a win condition
template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::is_win() {
    {

        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (check_line(i, j)) {
                    return true;
                }
            }
        }
    }

    return false;
}


// Update the board
template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (!is_within_bounds(x, y) || this->board[x][y] != '-') {
        cout << "Invalid move. Try again.\n";
        return false;
    }
    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
}


template <typename T>
void Word_Tic_Tac_Toe_Board<T>::display_board() {
    for (int i = 0 ; i < this->rows ; i++) {
        for (int j = 0 ; j < this->columns ; j++) {
            cout << "| " << this->board[i][j] << " |";
        }
        cout << endl;
    }

}

// Check for a draw
template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}

// Check if the game is over
template <typename T>
bool Word_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


/// ----------------------------------------------------------------------------------------- Pyramid Player class


template <typename T>
class Word_Tic_Tac_Toe_Player : public Player<T>{
public:
    Word_Tic_Tac_Toe_Player(string n, T symbol = '-') ;
    void getmove(int& x, int& y) override;
};





template <typename T>
Word_Tic_Tac_Toe_Player<T>::Word_Tic_Tac_Toe_Player(string n, T symbol) : Player<T>(n, symbol) {}

template <typename T>
void Word_Tic_Tac_Toe_Player<T>::getmove(int& x, int& y) {
    // Implementation for getting the move (can be extended)
    string CT;
    string strX, strY;
    cout << this->name << " turn " << endl;
    while (true) {
        cout << "Enter the row: ";
        cin >> strX;

        // Check if the input is numeric
        if (!strX.empty() && all_of(strX.begin(), strX.end(), ::isdigit)) {
            x = stoi(strX); // Convert string to integer
            break;
        } else {
            cout << "Invalid input. Please enter a valid numeric row.\n";
        }
    }

    while (true) {
        cout << "Enter the column: ";
        cin >> strY;

        // Check if the input is numeric
        if (!strY.empty() && all_of(strY.begin(), strY.end(), ::isdigit)) {
            y = stoi(strY); // Convert string to integer
            break;
        } else {
            cout << "Invalid input. Please enter a valid numeric column.\n";
        }
    }

    do {
        cout << "Enter the character you want to put\n";
        cin >> CT;
        CT[0] = toupper(CT[0]);
        if(CT.length() > 1 || CT[0] < 'A' || CT[0] > 'Z'){
            cout << "Invalid character. Please enter a single character (make it capital)\n";
        }
    }while(CT.length() > 1 || CT[0] < 'A' || CT[0] > 'Z');
    this->symbol = toupper(CT[0]);

}


/// ----------------------------------------------------------------------------------  Random player Pyramid class

template <typename T>
class Word_Tic_Tac_Toe_Random_Player : public RandomPlayer<T> {
public:
    Word_Tic_Tac_Toe_Random_Player(string n,T symbol = '-');

    // Generates a random move for the pyramid board.
    void getmove(int& x, int& y);
};

template <typename T>
Word_Tic_Tac_Toe_Random_Player<T>::Word_Tic_Tac_Toe_Random_Player(string n, T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = n + "_Habida";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Word_Tic_Tac_Toe_Random_Player<T>::getmove(int& x, int& y) {
    cout << this->name << " Turn" << endl;
    x = rand() % 3;
    y = rand() % 3;
    char CT;
    do {
        CT = rand() % 128; // Generate a random value in the full ASCII range
    } while (CT < 65 || CT > 90); // Ensure it is between 'A' (65) and 'Z' (90)
    cout << "Generated Char: " << static_cast<int>(CT) << " (" << CT << ")" << endl;
    this->symbol = CT;

}






/// -----------------------------------------------------------------------------------------------



void Word_Tic_tac_toe_rules() {
    cout << "4- Word Tic-Tac-Toe\n\n";
    cout << "Word Tic-Tac-Toe is an innovative twist on the classic Tic-Tac-Toe game. Instead of using 'X' or 'O', players place letters on a 3x3 grid to form valid words. This version adds a linguistic challenge to the traditional game mechanics.\n";
    cout << "Players aim to form a valid word with the letters they place on the board. Words can be formed horizontally, vertically, or diagonally.\n";
    cout << "\nRules:\n";
    cout << "1. Each player takes turns placing one letter on the board.\n";
    cout << "2. A player must try to form a valid word with each move.\n";
    cout << "3. Players can build upon existing letters to form words, provided that the resulting sequence is a valid word.\n";
    cout << "4. Winning: The game is won by forming a valid word horizontally, vertically, or diagonally.\n";
    cout << "5. If the board fills up without a valid word being formed, the game ends in a draw.\n";
    cout << "\nAdditional Details:\n";
    cout << "  - A file named dic.txt will be provided, containing all valid 3-letter words.\n";
    cout << "  - Your win-checking function should efficiently search this file to determine if a valid word is formed after each move.\n";
    cout << "\nBoard Shape:\n";
    cout << "| - || - || - |\n";
    cout << "| - || - || - |\n";
    cout << "| - || - || - |\n";
    cout << "\nGood luck, and may the best word win!\n";
}


void Word_Tic_tac_toe() {

    Word_Tic_tac_toe_rules();
    string choicePlayerType;
    Player<char>* players[2];
    Board<char>* Word_XO = new Word_Tic_Tac_Toe_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to Word Tic-Tac-Toe Game.\n";

    // Set up Player 1
    while (true) {
        choicePlayerType = "";
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice: ";
        cin >> choicePlayerType;

        if (choicePlayerType == "1" || choicePlayerType == "2") {
            cout << "Enter Player 1 name: ";
            cin >> player1Name;
            if (choicePlayerType == "1") {
                players[0] = new Word_Tic_Tac_Toe_Player<char>(player1Name);
            } else {
                players[0] = new Word_Tic_Tac_Toe_Random_Player<char>(player1Name);
            }
            break;
        } else {
            cout << "Invalid choice. Please choose 1 or 2.\n";
        }
    }

    // Ensure Player 2 has a unique name
    while (true) {
        cout << "Enter Player 2 name (different from Player 1): ";
        cin >> player2Name;
        if (player2Name != player1Name) {
            break;
        } else {
            cout << "Player 2 name cannot be the same as Player 1. Try again.\n";
        }
    }

    while (true) {
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "Enter your choice: ";
        cin >> choicePlayerType;

        if (choicePlayerType == "1") {
            players[1] = new Word_Tic_Tac_Toe_Player<char>(player2Name);
            break;
        } else if (choicePlayerType == "2") {
            players[1] = new Word_Tic_Tac_Toe_Random_Player<char>(player2Name);
            break;
        } else {
            cout << "Invalid choice. Please choose 1 or 2.\n";
        }
    }

    // Assign board to players
    players[0]->setBoard(Word_XO);
    players[1]->setBoard(Word_XO);

    // Display game setup
    cout << "(" << players[0]->getname() << ") with symbol (" << players[0]->getsymbol() << ") vs ("
         << players[1]->getname() << ") with symbol (" << players[1]->getsymbol() << ")\n";

    // Run the game
    GameManager<char> Word_Game(Word_XO, players);
    Word_Game.run();

    // Clean up
    delete players[0];
    delete players[1];
    delete Word_XO;

    return;
}

#endif //FINAL_BOAED_GAME_VERSION_WORD_TIC_TAC_TOE_H
