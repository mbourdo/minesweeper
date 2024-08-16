// Author: Michelle Bourdon   (Student ID: 251223429)
// Description: Declaration of the MinesweeperLogic class for the Minesweeper game.
//              This class contains the logic for the Minesweeper game board, including bomb placement
//              and calculation of neighboring bomb counts.
// Date: Feb 6, 2024
#ifndef MINESWEEPERLOGIC_H
#define MINESWEEPERLOGIC_H

#include <QObject>
#include <cstdlib>
#include <ctime>

// Constants
#define MAX_ROWS    16
#define MAX_COLS    30
#define MAX_BOMBS   99
#define BOMB_VALUE  -1


class MinesweeperLogic : public QObject{
    Q_OBJECT    // Q_OBJECT tells QT compiler to allow class to use signals & slots

// Class methods & attributes 
public:
    // Create and delete class instances
    MinesweeperLogic(QObject *parent = nullptr);
    ~MinesweeperLogic();
    
    // Public Methods - Get/Check & Set
    bool isBomb(int row, int col) const;
    bool isClicked(int row, int col) const;
    void setClicked(int row, int col);
    void addMove();
    int getMoves();
    int getNeighborBombCount(int row, int col) const;

    // Constants for Game 
    static const int rows = 16;  // Default = 16
    static const int cols = 30;  // Default = 30    
    static const int bombs = 99; // Default = 99
    static const int winMoves = rows * cols - bombs;

private:
    // Data structures
    bool bombGrid[rows][cols];
    int neighborBombCount[rows][cols];
    bool clickedGrid[rows][cols];
    int movesMade;

    // Interal Helper functions
    void placeBombs();
    void setNeighborBombCounts();
};

#endif // MINESWEEPERLOGIC_H
