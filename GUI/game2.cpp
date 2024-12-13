#include "game2.h"
#include "ui_game2.h"
#include "games_menu.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include<QTimer>

Game2::Game2(QWidget *parent) : QDialog(parent), ui(new Ui::Game2) {
    ui->setupUi(this);
    setupGameBoard();

    // Hide the game board by default
    ui->boardWidget->setVisible(false);
    ui->currentPlayerLabel->setVisible(false);
    ui->newGameButton->setVisible(false);

}

Game2::~Game2() {
    delete ui;
}
void getMove(int &gridRow, int &gridCol, int &row, int &col, bool gameBoard[3][3][3][3]) {
    do {
        gridRow = rand() % 3;
        gridCol = rand() % 3;
        row = rand() % 3;
        col = rand() % 3;
    } while (gameBoard[gridRow][gridCol][row][col]); // Ensure the move is on an empty cell
}
void Game2::setupGameBoard() {
    QGridLayout *gridLayout = new QGridLayout(ui->boardWidget); // Attach layout to boardWidget

    // Darker background and smooth borders for the main game board
    ui->boardWidget->setStyleSheet("background-color: #121212; border: 2px solid #444; border-radius: 10px;");

    for (int gridRow = 0; gridRow < 3; ++gridRow) {
        for (int gridCol = 0; gridCol < 3; ++gridCol) {
            QGroupBox *groupBox = new QGroupBox(this);
            groupBox->setStyleSheet("background-color: #1e1e1e; border: 1px solid #333; border-radius: 10px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);");
            QGridLayout *smallGridLayout = new QGridLayout(groupBox);

            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    QPushButton *button = new QPushButton(groupBox);
                    button->setMinimumSize(60, 60);
                    button->setStyleSheet("font-size: 24px; background-color: #333333; color: #ffffff; border: 1px solid #444444; border-radius: 10px;");
                    button->setFocusPolicy(Qt::NoFocus);

                    // Hover effect for buttons
                    button->setStyleSheet(button->styleSheet() + " :hover { background-color: #444444; border-color: #55aaff; transition: all 0.2s ease-in-out; }");

                    // Add button to the small grid layout
                    smallGridLayout->addWidget(button, row, col);

                    // Save button in board array
                    boardButtons[gridRow][gridCol][row][col] = button;
                    gameBoard[gridRow][gridCol][row][col] = false;

                    // Connect button click signal
                    connect(button, &QPushButton::clicked, [this, gridRow, gridCol, row, col]() {
                        handleCellClick(gridRow, gridCol, row, col);
                    });
                }
            }
            gridLayout->addWidget(groupBox, gridRow, gridCol);
        }
    }
}


void Game2::handleCellClick(int gridRow, int gridCol, int row, int col) {
    if (gameBoard[gridRow][gridCol][row][col] || gameover) {
        // If the game is over, no further moves are allowed
        return;
    }

    updateGameState(gridRow, gridCol, row, col, currentSymbol);


    if (checkSmallGridWinner(gridRow, gridCol)) {
        QMessageBox::information(this, "Small Grid Winner", currentPlayer + " wins in small grid " + QString::number(gridRow) + "," + QString::number(gridCol));
        blockSmallGrid(gridRow, gridCol);  // Block the grid after winning
        drawLargeSymbol(gridRow, gridCol);  // Draw large symbol in the winning small grid
        if (checkWinner()) {
            QMessageBox::information(this, "Game Over", currentPlayer + " wins!", QMessageBox::Ok, QMessageBox::Ok);
            gameover = true;  // Set game over flag to true
            disableboard();   // Disable all buttons on the board
            return;
        }
    }

    switchPlayer();
}



void Game2::updateGameState(int gridRow, int gridCol, int row, int col, const QString &symbol) {
    // Mark the cell as occupied and set the symbol
    gameBoard[gridRow][gridCol][row][col] = true;
    boardButtons[gridRow][gridCol][row][col]->setText(symbol);

    // Set the color and style based on the symbol
    if (symbol == "X") {
        boardButtons[gridRow][gridCol][row][col]->setStyleSheet("font-size: 24px; color: #ff4081; background-color: #333333; border: 2px solid #ff4081; transition: all 0.2s ease;");
    } else if (symbol == "O") {
        boardButtons[gridRow][gridCol][row][col]->setStyleSheet("font-size: 24px; color: #00bcd4; background-color: #333333; border: 2px solid #00bcd4; transition: all 0.2s ease;");
    }
}

void Game2::drawLargeSymbol(int gridRow, int gridCol) {
    QLabel *label = new QLabel(ui->boardWidget);
    label->setText(currentSymbol);
    label->setStyleSheet("font-size: 60px; color: #ffffff;");

    // Dynamic color for the symbol
    if (currentSymbol == "X") {
        label->setStyleSheet("font-size: 60px; color: #ff4081;");
    } else if (currentSymbol == "O") {
        label->setStyleSheet("font-size: 60px; color: #00bcd4;");
    }

    label->setAlignment(Qt::AlignCenter);

    // Ensure layout is valid before adding the label
    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->boardWidget->layout());
    if (layout) {
        layout->addWidget(label, gridRow, gridCol);
    }
}

void Game2::blockSmallGrid(int gridRow, int gridCol) {
    // Disable all buttons in the winning small grid
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            boardButtons[gridRow][gridCol][row][col]->setEnabled(false);
        }
    }
}


void Game2::switchPlayer() {
    if (currentPlayer == player1Name) {
        currentPlayer = player2Name;
        currentSymbol = player2Symbol;

        if (isRandomPlayerActive) {
            int gridRow, gridCol, row, col;
            getMove(gridRow, gridCol, row, col, gameBoard);

            // Simulate random player's move
            QTimer::singleShot(500, [this, gridRow, gridCol, row, col]() {
                handleCellClick(gridRow, gridCol, row, col);
            });

            return; // Prevent further manual input
        }
    } else {
        currentPlayer = player1Name;
        currentSymbol = player1Symbol;
    }

    ui->currentPlayerLabel->setText("Current Player: " + currentPlayer);
    ui->currentPlayerLabel->setStyleSheet("color: #ffffff; font-size: 20px; font-family: 'Arial', sans-serif;");
}


bool Game2::checkSmallGridWinner(int gridRow, int gridCol) {
    // Iterate over the rows of the small grid
    for (int row = 0; row < 3; ++row) {
        // Check if all three buttons in this row have the same symbol
        if (boardButtons[gridRow][gridCol][row][0]->text() == currentSymbol &&
            boardButtons[gridRow][gridCol][row][1]->text() == currentSymbol &&
            boardButtons[gridRow][gridCol][row][2]->text() == currentSymbol) {
            return true;  // Row match found
        }
    }

    // Iterate over the columns of the small grid
    for (int col = 0; col < 3; ++col) {
        // Check if all three buttons in this column have the same symbol
        if (boardButtons[gridRow][gridCol][0][col]->text() == currentSymbol &&
            boardButtons[gridRow][gridCol][1][col]->text() == currentSymbol &&
            boardButtons[gridRow][gridCol][2][col]->text() == currentSymbol) {
            return true;  // Column match found
        }
    }

    // Check the main diagonal of the small grid
    if (boardButtons[gridRow][gridCol][0][0]->text() == currentSymbol &&
        boardButtons[gridRow][gridCol][1][1]->text() == currentSymbol &&
        boardButtons[gridRow][gridCol][2][2]->text() == currentSymbol) {
        return true;  // Diagonal match found
    }

    // Check the anti-diagonal of the small grid
    if (boardButtons[gridRow][gridCol][0][2]->text() == currentSymbol &&
        boardButtons[gridRow][gridCol][1][1]->text() == currentSymbol &&
        boardButtons[gridRow][gridCol][2][0]->text() == currentSymbol) {
        return true;  // Anti-diagonal match found
    }

    return false;  // No winner in this small grid
}
bool Game2::checkWinner() {
    const int blockSize = 3;

    bool smallGridOccupied[blockSize][blockSize] = {false};  // Track which small grids have a winner

    // Check for a winner in each small grid (3x3 sub-grid)
    for (int i = 0; i < blockSize; ++i) {
        for (int j = 0; j < blockSize; ++j) {
            if (checkSmallGridWinner(i, j)) {
                smallGridOccupied[i][j] = true;  // Mark the small grid as occupied by a winner
            }
        }
    }

    // Check the large 3x3 grid for a winner (i.e., 3 small grid wins in a row)
    // Check rows of small grid winners
    for (int i = 0; i < blockSize; ++i) {
        if (smallGridOccupied[i][0] && smallGridOccupied[i][1] && smallGridOccupied[i][2]) {
            return true;  // Horizontal win in the large grid
        }
    }

    // Check columns of small grid winners
    for (int j = 0; j < blockSize; ++j) {
        if (smallGridOccupied[0][j] && smallGridOccupied[1][j] && smallGridOccupied[2][j]) {
            return true;  // Vertical win in the large grid
        }
    }

    // Check the diagonal of small grid winners
    if (smallGridOccupied[0][0] && smallGridOccupied[1][1] && smallGridOccupied[2][2]) {
        return true;  // Diagonal win in the large grid
    }

    // Check the anti-diagonal of small grid winners
    if (smallGridOccupied[0][2] && smallGridOccupied[1][1] && smallGridOccupied[2][0]) {
        return true;  // Anti-diagonal win in the large grid
    }

    return false;  // No winner in the large grid
}



void Game2::on_playVsRandomButton_clicked() {
    bool ok;
    player1Name = QInputDialog::getText(this, "Player 1 Name", "Enter Player 1's name:", QLineEdit::Normal, "", &ok);
    if (!ok || player1Name.isEmpty()) return;

    player2Name = "Mr. Habida";
    QStringList symbols = {"X", "O"};
    player1Symbol = QInputDialog::getItem(this, "Choose Symbol", "Choose Player 1's symbol:", symbols, 0, false, &ok);
    if (!ok || player1Symbol.isEmpty()) return;

    symbols.removeAll(player1Symbol);
    player2Symbol = symbols[0];

    currentPlayer = player1Name;
    currentSymbol = player1Symbol;
    isRandomPlayerActive = true;

    QMessageBox::information(this, "Game Setup", "Player 1: " + player1Name + " (" + player1Symbol + ")\nPlayer 2: " + player2Name + " (" + player2Symbol + ")", QMessageBox::Ok, QMessageBox::Ok);

    // Show the game board
    ui->boardWidget->setVisible(true);
    ui->currentPlayerLabel->setVisible(true);
    ui->newGameButton->show();
    ui->playVsRandomButton->hide();
    ui->playVsSecondButton->hide();
}


void Game2::on_playVsSecondButton_clicked() {
    bool ok;
    player1Name = QInputDialog::getText(this, "Player 1 Name", "Enter Player 1's name:", QLineEdit::Normal, "", &ok);
    if (!ok || player1Name.isEmpty()) return;

    player2Name = QInputDialog::getText(this, "Player 2 Name", "Enter Player 2's name:", QLineEdit::Normal, "", &ok);
    if (!ok || player2Name.isEmpty()) return;

    QStringList symbols = {"X", "O"};
    player1Symbol = QInputDialog::getItem(this, "Choose Symbol", "Choose Player 1's symbol:", symbols, 0, false, &ok);
    if (!ok || player1Symbol.isEmpty()) return;

    symbols.removeAll(player1Symbol);
    player2Symbol = symbols[0];

    currentPlayer = player1Name;
    currentSymbol = player1Symbol;

    QMessageBox::information(this, "Game Setup", "Player 1: " + player1Name + " (" + player1Symbol + ")\nPlayer 2: " + player2Name + " (" + player2Symbol + ")");

    // Show the game board
    ui->boardWidget->setVisible(true);
    ui->newGameButton->show();
    ui->playVsRandomButton->hide();
    ui->playVsSecondButton->hide();
}

void Game2::on_helpButton_clicked() {
    QMessageBox::information(this, "How to Play", "In Ultimate Tic Tac Toe, you play on a 3x3 grid of 9 smaller Tic Tac Toe boards.\n"
                                                  "Each move you make sends your opponent to a specific small grid.\n"
                                                  "The goal is to win in one of the smaller grids and ultimately the large grid.");
}

void Game2::on_backButton_clicked() {
    // Enable the board before going back to the menu
    enableboard();

    // Proceed with navigating back to the games menu
    GamesMenu *gamesMenu = new GamesMenu(this);
    gamesMenu->show();
    this->close();
}




void Game2::on_newGameButton_clicked()
{
    resetBoard();
    enableboard();  // Ensure board is enabled when starting a new game

    ui->playVsRandomButton->setVisible(true);
    ui->playVsSecondButton->setVisible(true);
    ui->newGameButton->setVisible(false);
    ui->boardWidget->hide();
    ui->currentPlayerLabel->hide();
}


void Game2::resetBoard() {
    enableboard();  // Ensure board is enabled during reset

    for (int gridRow = 0; gridRow < 3; ++gridRow) {
        for (int gridCol = 0; gridCol < 3; ++gridCol) {
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    // Clear the text on each button
                    boardButtons[gridRow][gridCol][row][col]->setText("");
                    // Reset the button style
                    boardButtons[gridRow][gridCol][row][col]->setStyleSheet("font-size: 24px; background-color: #333333; color: #ffffff; border: 1px solid #444444; border-radius: 10px;");
                    // Enable the button again
                    boardButtons[gridRow][gridCol][row][col]->setEnabled(true);
                    // Reset the game state for each small grid
                    gameBoard[gridRow][gridCol][row][col] = false;
                }
            }
        }
    }

    // Reset any variables used to track the current state
    currentPlayer = player1Name;
    currentSymbol = player1Symbol;

    // Update the label with the current player
    ui->currentPlayerLabel->setText("Current Player: " + currentPlayer);

    // Clear any large symbol labels drawn on the board (if any)
    QList<QLabel*> labels = ui->boardWidget->findChildren<QLabel*>();
    for (QLabel* label : labels) {
        label->deleteLater();
    }

    // Reset any small grid occupation tracking (if applicable)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            smallGridOccupied[i][j] = false;
        }
    }
}

void Game2::disableboard(){
    // Disable all buttons on the board
    for (int gridRow = 0; gridRow < 3; ++gridRow) {
        for (int gridCol = 0; gridCol < 3; ++gridCol) {
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    boardButtons[gridRow][gridCol][row][col]->setEnabled(false);
                }
            }
        }
    }
}
void Game2::enableboard(){
    for (int gridRow = 0; gridRow < 3; ++gridRow) {
        for (int gridCol = 0; gridCol < 3; ++gridCol) {
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    boardButtons[gridRow][gridCol][row][col]->setEnabled(true);
                }
            }
        }
    }
}
