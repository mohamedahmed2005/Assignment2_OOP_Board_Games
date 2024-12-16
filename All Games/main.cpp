#include "BoardGame_Classes.h"
#include "Four_in_a_row.h"
#include "Misere_X_O.h"
#include "Numerical_Tic_Tac_Toe.h"
#include "pyramid.h"
#include "Ultimate_Tic_Tac_Toe.h"
#include "Word-Tic-tac-toe.h"
#include "X_O_4x4.h"
#include "X_O_5x5.h"
#include "SUS_X_O.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void menu() {
	int width = 90;
	string title = "Welcome to the Arcade";
	cout << string(width, '-') << "\n";
	int space = (width - title.length()) / 2;
	cout << string(space, ' ') << title << "\n";
	cout << string(width, '-') << "\n\n";
	while (true) {

		cout << "\nWhat Do you want to Play?\n\n";
		cout << "[1] Pyramic Tic-Tac-Toe\n[2] Four-in-a-row\n[3] 5 x 5 Tic Tac Toe\n";
		cout << "[4] Word Tic Tac Toe\n[5] Numerical Tic Tac Toe\n[6] Misere Tic Tac Toe\n";
		cout << "[7] 4 x 4 Tic Tac Toe\n[8] Ultimate Tic Tac Toe\n[9] SUS Game\n";
		cout << "[10] Exit the Program\n\n";
		cout << "Please enter you choice:";
		int choice;
		cin >> choice;
		while (cin.fail() || (choice < 1 || choice > 10)) {
			cin.clear(); // Clear the error flag
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please choose between 1-10.\n\n";
			cout << "What Do you want to Play?\n\n";
			cout << "[1] Pyramic Tic-Tac-Toe\n[2] Four-in-a-row\n[3] 5 x 5 Tic Tac Toe\n";
			cout << "[4] Word Tic Tac Toe\n[5] Numerical Tic Tac Toe\n[6] Misere Tic Tac Toe\n";
			cout << "[7] 4 x 4 Tic Tac Toe\n[8] Ultimate Tic Tac Toe\n[9] SUS Game\n";
			cout << "[10] Exit the Program\n\n";
			cout << "Please enter you choice:";
			cin >> choice;
		}
		if (choice == 1) {
			PyramidGame();
		}
		else if (choice == 2) {
			Four_in_a_row_menu();
		}
		else if (choice == 3) {
			X_O_5x5_Gameplay();
		}
		else if (choice == 4) {
			Word_Tic_tac_toe();
		}
		else if (choice == 5) {
			Numerical_menu();
		}
		else if (choice == 6) {
			Misere_X_O_Gameplay();
		}
		else if (choice == 7) {
			X_O_4x4_Gameplay();
		}
		else if (choice == 8) {
			Ultimate_Tic_Tac_Toe_menu();
		}
		else if (choice == 9) {
			SUS_Gameplay();
		}else if (choice == 10) {
			cout << "Thanks for using our Program :)\n";
			break;
		}

	}
	


}



int main() {
	menu();
	
	return 0;

}
