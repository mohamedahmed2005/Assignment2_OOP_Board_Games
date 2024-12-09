# Qt Game Collection

This repository contains two games designed using Qt:

1. **Ultimate Tic Tac Toe**  
2. **Four in a Row Tic Tac Toe**

These games are implemented with C++ and Qt Framework for a rich GUI experience.

## 1. Ultimate Tic Tac Toe

**Ultimate Tic Tac Toe** is a more complex version of the classic Tic Tac Toe game. It consists of 9 smaller Tic Tac Toe grids arranged in a 3x3 layout. The gameplay rules are:

- Players take turns selecting a small grid to place their symbol (X or O).
- The selection of a small grid is determined by the location of the previous player's move in the larger grid.
- The objective is to win in any of the smaller grids or the larger grid by forming three consecutive symbols in a row, column, or diagonal.

### Features:
- Playable in two-player mode.
- Interactive user interface with a clean and responsive design.
- Resets the board when a game is finished.
- Displays the current player and win status.

### How to Play:
1. Click on any empty cell in a small grid to make your move.
2. The location of the move determines the small grid for the next player's move.
3. Continue playing until one player wins, or all grids are filled.
4. Reset the game by clicking the reset button.

### Key Qt Components:
- **QPushButton** for board interactions.
- **QLabel** for displaying player information and win status.
- **QVBoxLayout** and **QHBoxLayout** for responsive layout.
- **QGridLayout** for organizing the board grid.

## 2. Four in a Row Tic Tac Toe

**Four in a Row Tic Tac Toe** is an advanced version of the classic Tic Tac Toe game where players need to connect four symbols in a row to win. This game is typically played on a 6x7 grid.

### Features:
- Two-player mode with player symbols X and O.
- Users can click on a column to drop their symbol into the lowest available row.
- Game status updates to indicate the winner or if the game is a draw.
- Visual and interactive UI for an enhanced user experience.

### How to Play:
1. Click on a column to drop your symbol.
2. The symbol will fall to the lowest empty row in the selected column.
3. Continue playing until one player forms a row of four symbols or the board is full.
4. Reset the game by clicking the reset button.

### Key Qt Components:
- **QPushButton** for dropping symbols into columns.
- **QLabel** for game status and player information.
- **QGridLayout** for organizing the 6x7 game board.
- **QStackedWidget** for managing multiple views (if needed).

## Getting Started

### Prerequisites:
- **Qt** (Version 5 or higher) installed on your machine.
- A C++ compiler like **g++** or **MSVC**.

### Clone the Repository:
```bash
git clone https://github.com/your-username/qt-game-collection.git
