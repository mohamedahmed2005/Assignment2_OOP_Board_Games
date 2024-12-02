//
// Created by Amr khaled on 12/1/2024.
//

#ifndef A2_T2_P1_4_AI_PYRAMIDPLAYER_H
#define A2_T2_P1_4_AI_PYRAMIDPLAYER_H
#include "Pyramid.h"
#include "BoardGame_Classes.h"
#include <limits>
#include <algorithm>


template <typename T>
class Pyramid_MinMax_Player : public Player<T> {
public:
    explicit Pyramid_MinMax_Player(T symbol);

    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T currentSymbol, bool isMaximizing);
    std::pair<int, int> getBestMove();

};

//--------------------------------------- IMPLEMENTATION

template <typename T>
Pyramid_MinMax_Player<T>::Pyramid_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

// Public method to get the AI's move
template <typename T>
void Pyramid_MinMax_Player<T>::getmove(int& x, int& y) {
    std::pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

// Minimax algorithm
template <typename T>
int Pyramid_MinMax_Player<T>::calculateMinMax(T currentSymbol, bool isMaximizing) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? -1 : 1;
    } else if (this->boardPtr->is_draw()) {
        return 0;
    }

    T opponentSymbol = (currentSymbol == 'X') ? 'O' : 'X';
    int bestValue = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    for (int i = 0; i < this->boardPtr->size(); ++i) {
        for (int j = 0; j <= i; ++j) { // Pyramid structure
            if (this->boardPtr->update_board(i, j, currentSymbol)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (isMaximizing) {
                    bestValue = std::max(bestValue, value);
                } else {
                    bestValue = std::min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

// Get the best move for the AI
template <typename T>
std::pair<int, int> Pyramid_MinMax_Player<T>::getBestMove() {
    int bestValue = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < this->boardPtr->size(); ++i) {
        for (int j = 0; j <= i; ++j) { // Pyramid structure
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(i, j, 0); // Undo move

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}




#endif //A2_T2_P1_4_AI_PYRAMIDPLAYER_H
