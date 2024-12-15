//
// Created by VICTUS on 12/7/2024.
//

#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H
#include"BoardGame_Classes.h"
using namespace std;
enum BlockState { OPEN, CLOSED }; // to check if subboard is closed or not, set Open = 0 and Closed = 1
map<pair<int, int>, bool> availablePoints;

template<typename T>
class Ultimate_Tic_Tac_Toe_Board:public Board<T> {
private:
    BlockState blockStatus[3][3];
    public:
    Ultimate_Tic_Tac_Toe_Board();
    void display_board() override;
    bool update_board(int x, int y, T symbol) override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
template<typename T>
Ultimate_Tic_Tac_Toe_Board<T>::Ultimate_Tic_Tac_Toe_Board() {
    this->rows = 9;
    this->columns = 9;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        fill(this->board[i], this->board[i] + this->columns, '.');
    }
    // Initialize all submatrices as OPEN
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            blockStatus[i][j] = OPEN;
        }
    }
}
template <typename T>
void Ultimate_Tic_Tac_Toe_Board<T>::display_board() {
    const int blockSize = 3; // Size of a block

    // Print the header row showing the number of columns above each column
    cout << "   "; // Offset for row numbers
    for (int j = 0; j < this->columns; ++j) {
        cout << " " << j << " ";
        if ((j + 1) % blockSize == 0 && j < this->columns - 1) {
            cout << " # "; // Block boundary
        } else if (j < this->columns - 1) {
            cout << " | "; // Column separator
        }
    }
    cout << endl;

    // Iterate over each row
    for (int i = 0; i < this->rows; ++i) {
        // Print the row with cell values
        cout << i << "  "; // Number of rows behind this row
        for (int j = 0; j < this->columns; ++j) {
            cout << " " << this->board[i][j] << " "; // Print cell content with padding
            if ((j + 1) % blockSize == 0 && j < this->columns - 1) {
                cout << " # "; // Block boundary
            } else if (j < this->columns - 1) {
                cout << " | "; // Cell separator
            }
        }
        cout << endl;

        // Print horizontal divider except for the last row
        if ((i + 1) % blockSize == 0 && i < this->rows - 1) {
            cout << "   "; // Offset for row numbers
            for (int j = 0; j < this->columns; ++j) {
                cout << "==="; // Thicker divider for block boundaries
                if (j < this->columns - 1) {
                    if ((j + 1) % blockSize == 0) {
                        cout << " # "; // Block boundary
                    } else {
                        cout << " + "; // Intersection of lines
                    }
                }
            }
            cout << endl;
        } else if (i < this->rows - 1) {
            cout << "   "; // Offset for row numbers
            for (int j = 0; j < this->columns; ++j) {
                cout << "---"; // Regular divider
                if (j < this->columns - 1) {
                    if ((j + 1) % blockSize == 0) {
                        cout << " # "; // Block boundary
                    } else {
                        cout << " + "; // Intersection of lines
                    }
                }
            }
            cout << endl;
        }
    }
}


template<typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns) {
        return false;
    }

    int blockRow = x / 3; // Determine which submatrix this cell belongs to
    int blockCol = y / 3;

    // Check if the submatrix is CLOSED
    if (blockStatus[blockRow][blockCol] == CLOSED) {
        cout << "This block is closed. Please choose a different block." << endl;
        return false;
    }

    if (this->board[x][y] != '.') {
        return false;
    }

    // Update the cell
    this->board[x][y] = symbol;
    ++this->n_moves;

    // Check if the submatrix should be closed
    bool submatrixWon = false;

    // Check rows, columns, and diagonals within the submatrix
    int startRow = blockRow * 3;
    int startCol = blockCol * 3;

    for (int i = 0; i < 3; ++i) {
        if (this->board[startRow + i][startCol] == symbol &&
            this->board[startRow + i][startCol + 1] == symbol &&
            this->board[startRow + i][startCol + 2] == symbol) {
            submatrixWon = true;
            break;
        }
        if (this->board[startRow][startCol + i] == symbol &&
            this->board[startRow + 1][startCol + i] == symbol &&
            this->board[startRow + 2][startCol + i] == symbol) {
            submatrixWon = true;
            break;
        }
    }

    if (!submatrixWon) {
        if (this->board[startRow][startCol] == symbol &&
            this->board[startRow + 1][startCol + 1] == symbol &&
            this->board[startRow + 2][startCol + 2] == symbol) {
            submatrixWon = true;
        }
        if (this->board[startRow][startCol + 2] == symbol &&
            this->board[startRow + 1][startCol + 1] == symbol &&
            this->board[startRow + 2][startCol] == symbol) {
            submatrixWon = true;
        }
    }

    // If submatrix is won or full, mark it as CLOSED
    bool submatrixFull = true;
    for (int i = startRow; i < startRow + 3; ++i) {
        for (int j = startCol; j < startCol + 3; ++j) {
            if (this->board[i][j] == '.') {
                submatrixFull = false;
                break;
            }
        }
    }

    if (submatrixWon || submatrixFull) {
        blockStatus[blockRow][blockCol] = CLOSED;
    }

    return true;
}


template<typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_win() {
    const int blockSize = 3;
    T mainBoard[blockSize][blockSize];

    // Aggregate smaller board results into the main board
    for (int i = 0; i < blockSize; ++i) {
        for (int j = 0; j < blockSize; ++j) {
            int startRow = i * blockSize;
            int startCol = j * blockSize;
            T winner = '.';

            // Check the smaller board
            for (int r = startRow; r < startRow + blockSize; ++r) {
                if (this->board[r][startCol] != '.' && this->board[r][startCol] == this->board[r][startCol + 1] && this->board[r][startCol + 1] == this->board[r][startCol + 2]) {
                    winner = this->board[r][startCol];
                    break;
                }
            }

            for (int c = startCol; c < startCol + blockSize; ++c) {
                if (this->board[startRow][c] != '.' && this->board[startRow][c] == this->board[startRow + 1][c] && this->board[startRow + 1][c] == this->board[startRow + 2][c]) {
                    winner = this->board[startRow][c];
                    break;
                }
            }

            if (this->board[startRow][startCol] != '.' && this->board[startRow][startCol] == this->board[startRow + 1][startCol + 1] && this->board[startRow + 1][startCol + 1] == this->board[startRow + 2][startCol + 2]) {
                winner = this->board[startRow][startCol];
            }

            if (this->board[startRow][startCol + 2] != '.' && this->board[startRow][startCol + 2] == this->board[startRow + 1][startCol + 1] && this->board[startRow + 1][startCol + 1] == this->board[startRow + 2][startCol]) {
                winner = this->board[startRow][startCol + 2];
            }

            mainBoard[i][j] = winner;
        }
    }

    // Check if there's a win on the main board
    for (int i = 0; i < blockSize; ++i) {
        if (mainBoard[i][0] != '.' && mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2]) {
            return true;
        }
    }

    for (int i = 0; i < blockSize; ++i) {
        if (mainBoard[0][i] != '.' && mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i]) {
            return true;
        }
    }

    if (mainBoard[0][0] != '.' && mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2]) {
        return true;
    }

    if (mainBoard[0][2] != '.' && mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0]) {
        return true;
    }

    return false;
}
template<typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::is_draw() {
    // Check if all subboards are closed
    bool allBlocksClosed = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (blockStatus[i][j] == OPEN) {
                allBlocksClosed = false;
                break;
            }
        }
        if (!allBlocksClosed) {
            break;
        }
    }

    // If all blocks are closed and no winner, it's a draw
    return (allBlocksClosed && !is_win());
}

template<typename T>
bool Ultimate_Tic_Tac_Toe_Board<T>::game_is_over() {
    return is_win()||is_draw();
}
//---------------------------------------------------------------
template <typename T>
class Ultimate_Tic_Tac_Toe_player : public Player<T> {
public:
    Ultimate_Tic_Tac_Toe_player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override;
};
template<typename T>
void Ultimate_Tic_Tac_Toe_player<T>::getmove(int &x, int &y) {
    cout<<this->name<<"'s turn with symbol "<<this->symbol<<endl;
    cout<<"Please enter row and column between (0,8) : ";
    cin>>x >> y;
    while (cin.fail()) {
        cin.clear();
        cin.ignore();
        cout<<"Please enter row and column between (0,8) : ";
        cin>>x >> y;
    }
}
//-----------------------------------------------------------
template<typename T>
class Random_Ultimate_Tic_Tac_Toe : public RandomPlayer<T> {
    public:
    Random_Ultimate_Tic_Tac_Toe(string name,T symbol) : RandomPlayer<T>(symbol) {
        this->name = name+"_Random Computer";
        srand(static_cast<unsigned int>(time(NULL)));
    }
    void getmove(int& x, int& y) override;
};
template<typename T>
void Random_Ultimate_Tic_Tac_Toe<T>::getmove(int &x, int &y) {
    cout<<this->name<<"'s turn with symbol "<<this->symbol<<endl;

    // Initialize map of available points if it's empty
    if (availablePoints.empty()) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                availablePoints[{i, j}] = true; // All points initially available
            }
        }
    }

    // Copy available points to a vector
    vector<pair<int, int>> keys;
    for (const auto &entry : availablePoints) {
        if (entry.second) { // Only include available points
            keys.push_back(entry.first);
        }
    }

    // Check if there are no more available points
    if (keys.empty()) {
        cout << "No more moves available! Game Over." << endl;
        x = -1;
        y = -1;
        exit(0); // Terminate program gracefully
    }

    // Randomly select an index from the vector
    int randomIndex = rand() % keys.size();
    x = keys[randomIndex].first; // Extract x-coordinate
    y = keys[randomIndex].second; // Extract y-coordinate

    cout << "It chooses " << x << " " << y << endl;

    // Remove chosen point from the available points map
    availablePoints.erase({x, y});
}

int Ultimate_Tic_Tac_Toe_menu() {
    int choice;
    Board<char>* B = new Ultimate_Tic_Tac_Toe_Board<char>();
    Player<char>* players[2];
    string player1Name, player2Name;
    char x1 , x2;
    string choose;
    cout << "Welcome to FCAI Ultimate Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> player1Name;
    do {
        cout << "Choose Player X type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
    }while (cin.fail()||(choice<0||choice>2));
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
    if (choice == 1) {
        players[0] = new Ultimate_Tic_Tac_Toe_player<char>(player1Name,x1);
        cout << "Player X (" << player1Name << ") is a Human.\n";
    }
    else if (choice == 2) {
        players[0] = new Random_Ultimate_Tic_Tac_Toe<char>(player1Name,x1);
    }
    players[0]->setBoard(B);

    // Set up player 2
    cout << "Enter Player Y name: ";
    cin >> player2Name;
    do {
        cout << "Choose Player Y type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
    }while (cin.fail()||(choice<0||choice>3));
    if (choice == 1) {
        players[1] = new Ultimate_Tic_Tac_Toe_player<char>(player2Name,x2);
        cout << "Player Y (" << player2Name << ") is a Human.\n";
    }
    else if (choice == 2) {
        players[1] = new Random_Ultimate_Tic_Tac_Toe<char>(player2Name,x2);
    }
    players[0]->setBoard(B);
    GameManager<char> Ultimate_Tic_Tac_Toe(B, players);
    Ultimate_Tic_Tac_Toe.run();
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    availablePoints.clear();
    return 0;
}



#endif //ULTIMATE_TIC_TAC_TOE_
