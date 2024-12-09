#include <iostream>
#include "BoardGame_classes.h"
#include "Misere_X_O.h"
#include "X_O_5x5.h"
#include "X_O_4x4.h"
#include <string>

void run_problem3() {
    int choice;
    Player<char>* players[2];
    X_O_5x5_Board <char>* B = new X_O_5x5_Board <char>();
    string playerXName, player2Name;
    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    getline(cin, playerXName);
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;
    switch (choice) {
    case 1:
        players[0] = new X_O_5x5_Player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new X_O_5x5_Random_Player<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }
    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, player2Name);
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new X_O_5x5_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new X_O_5x5_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void run_problem6() {
    int choice;
    Player<char>* players[2];
    Misere_X_O_Board <char>* B = new Misere_X_O_Board <char>();
    string playerXName, player2Name;
    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    getline(cin, playerXName);
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;
    switch (choice) {
    case 1:
        players[0] = new Misere_X_O_Player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new Misere_X_O_Random_Player<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }
    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, player2Name);
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new Misere_X_O_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new Misere_X_O_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void run_problem7() {

    int choice;
    Player<char>* players[2];
    X_O_4x4_Board <char>* B = new X_O_4x4_Board <char>();
    string playerXName, player2Name;
    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    getline(cin, playerXName);
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;
    switch (choice) {
    case 1:
        players[0] = new X_O_4x4_Player<char>(playerXName, 'X');
        break;
    case 2:
        players[0] = new X_O_4x4_Random_Player<char>('X');
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        return;
    }
    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, player2Name);
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new X_O_4x4_Player<char>(player2Name, 'O');
        break;
    case 2:
        players[1] = new X_O_4x4_Random_Player<char>('O');
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        return;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

int main() {
    run_problem7();
    return 0;
}