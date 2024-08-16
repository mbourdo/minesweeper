// Author: Michelle Bourdon   (Student ID: 251223429)
// Description: Implementation of the MinesweeperLogic class for the Minesweeper game.
//              This class contains the logic for the Minesweeper game board, including bomb placement
//              and calculation of neighboring bomb counts.
// Date: Feb 6, 2024

#include "MinesweeperLogic.h"

// Function: MinesweeperLogic   (Constructor)
// Description: Initializes the Minesweeper game board logic, placing bombs randomly and 
//              calculating & setting neighboring bomb counts for each cell.
// Parameters:
//   - parent: Pointer to the parent QObject (default is nullptr).
MinesweeperLogic::MinesweeperLogic(QObject *parent)
    : QObject(parent)   {

    // Initialize Minesweeper game board logic
    srand(time(0));                                 // Seed rand with current time
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            clickedGrid[row][col] = false;          // Set 2D arrary to say nothing clicked
            bombGrid[row][col] = false;             // Set 2D arrary to store bomb locations
            neighborBombCount[row][col] = 0;        // Set 2D array of neighbor bomb counts
        }
    }
    placeBombs();                                   // Place bombs on board
    setNeighborBombCounts();                        // Calculate & set counts of neighbor bombs
    movesMade = 0;
}

// Function: ~MinesweeperLogic   (Destructor)
// Description: Cleanup resources 
MinesweeperLogic::~MinesweeperLogic() {
    // Cleanup resources
}

// Function: isBomb
// Description: Checks if the specified cell contains a bomb.
// Parameters:
//   - row: Row position of the cell to check.
//   - col: Column position of the cell to check.
// Returns: True if the cell contains a bomb, false otherwise.
bool MinesweeperLogic::isBomb(int row, int col) const {
    // Check if the specified cell contains a bomb
    return bombGrid[row][col];
}

// Function: isClicked
// Description: Checks if the specified cell has been clicked.
// Parameters:
//   - row: Row position of the cell to check.
//   - col: Column position of the cell to check.
// Returns: True if the cell has been clicked, false otherwise.
bool MinesweeperLogic::isClicked(int row, int col) const {
    // Check if the specified cell contains a bomb
    return clickedGrid[row][col];
}

// Function: setClicked
// Description: Sets the specified cell as clicked.
// Parameters:
//   - row: Row position of the cell to mark as clicked.
//   - col: Column position of the cell to mark as clicked.
void MinesweeperLogic::setClicked (int row, int col) {
    // Set to clicked
    clickedGrid[row][col] = true;
}

// Function: addMove
// Description: Increments the movesMade counter.
void MinesweeperLogic::addMove () {
    // increase counter
    movesMade++;
}

// Function: getMoves
// Description: Retrieves the current number of moves made.
// Returns: The number of moves made.
int MinesweeperLogic::getMoves() {
    return movesMade;
}

// Function: getNeighborBombCount
// Description: Retrieves the number of neighboring bombs for the specified cell.
// Parameters:
//   - row: Row position of the cell to check.
//   - col: Column position of the cell to check.
// Returns: The number of neighboring bombs for the specified cell.
int MinesweeperLogic::getNeighborBombCount(int row, int col) const {
    return neighborBombCount[row][col];
}

// Function: placeBombs
// Description: Places a specified number of bombs randomly on the game board.
void MinesweeperLogic::placeBombs() {
    int bombsToPlace = bombs;           // Initally, set # bombs left to place equal to total bombs
    while (bombsToPlace > 0) {          // Stop when none left to place
        int row = std::rand() % rows;   // random row value (0 .. row-1)
        int col = std::rand() % cols;   // random col value (0 .. col-1)

        // Check if a bomb is already placed at the selected position
        if (!bombGrid[row][col]) {
            bombGrid[row][col] = true;
            --bombsToPlace;
        }
    }
}

// Function: setNeighborBombCounts
// Description: Calculates and sets the number of neighboring bombs for each cell on the game board.
void MinesweeperLogic::setNeighborBombCounts() {
    // Calculate the number of neighboring bombs for each cell
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (bombGrid[row][col]) {           
                neighborBombCount[row][col] = BOMB_VALUE;   // Set bomb cells to -1
                continue;
            }
            // Count neighboring bombs - note bomb cells handled above
            int count = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int newRow = row + i;
                    int newCol = col + j;
                    if (newRow >= 0 && newRow < rows   // in board range
                     && newCol >= 0 && newCol < cols   // in board range
                     && bombGrid[newRow][newCol])  {   // checked cell is a bomb
                        ++count;
                    }
                }
            }
            // set final neighbor bomb count
            neighborBombCount[row][col] = count;
        }
    }
}
