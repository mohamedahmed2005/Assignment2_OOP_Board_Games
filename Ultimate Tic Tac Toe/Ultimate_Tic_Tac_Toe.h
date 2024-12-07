//
// Created by VICTUS on 12/7/2024.
//

#ifndef ULTIMATE_TIC_TAC_TOE_H
#define ULTIMATE_TIC_TAC_TOE_H
#include"BoardGame_Classes.h"
using namespace std;
template<typename T>
class Ultimate_Tic_Tac_Toe:public BoardGame_Classes<T> {
    public:
    Ultimate_Tic_Tac_Toe();
    void display_board() override;
    bool update_board(int x, int y, T symbol) override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};
template<typename T>
Ultimate_Tic_Tac_Toe<T>::Ultimate_Tic_Tac_Toe() {
    this->rows = 9;
    this->columns = 9;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns];
        fill(this->board[i], this->board[i] + this->columns, '.');
    }
}
template <typename T>
void Four_in_a_row_Board<T>::display_board() {
        const int blockSize = 3; // Size of a block

        // Iterate over each row
        for (int i = 0; i < this->rows; ++i) {
            // Print the row with cell values
            for (int j = 0; j < this->columns; ++j) {
                cout << "   "; // Space for cells
                if ((j + 1) % blockSize == 0 && j < this->columns - 1) {
                    cout << "#"; // Block boundary
                } else if (j < this->columns - 1) {
                    cout << "|"; // Cell separator
                }
            }
            cout << endl;

            // Print horizontal divider except for the last row
            if (i < this->rows - 1) {
                for (int j = 0; j < this->columns; ++j) {
                    if ((i + 1) % blockSize == 0) {
                        // Thicker divider for block boundaries
                        cout << "===";
                    } else {
                        // Regular divider
                        cout << "---";
                    }

                    if (j < this->columns - 1) {
                        if ((j + 1) % blockSize == 0) {
                            cout << "#"; // Block boundary
                        } else {
                            cout << "+"; // Intersection of lines
                        }
                    }
                }
                cout << endl;
            }
        }
}
template<typename T>
bool Ultimate_Tic_Tac_Toe<T>::game_is_over() {
    return is_win()||is_draw();
}



#endif //ULTIMATE_TIC_TAC_TOE_
