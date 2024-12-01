#include "Numerical_Tic_Tac_Toe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Seed the random number generator for the random moves
    srand(static_cast<unsigned int>(time(0)));

    // Create the board
    Numerical_Tic_Tac_Toe<int> board;

    // Create two players: Player 1 is a random player, Player 2 is a human player
    Numerical_Tic_Tac_Toe_player<int> player1("Ahmed",0); // Odd player
    Numerical_Tic_Tac_Toe_player<int> player2("Mohamed", 2); // Even player

    // Create an array of players
    Player<int>* players[2] = {&player1, &player2};

    // Create the game manager
    Numerical_Game_manager<int> gameManager(&board, players);

    // Run the game
    gameManager.run();

    return 0;
}
