// Author: Michelle Bourdon   (Student ID: 251223429)
// Description: Definition of the MainWindow class for the Minesweeper game.
//              This class represents the Qt-based user interface of the Minesweeper
//              application, including setup of all Qt comoponents, and changes to them.
// Date: Feb 6, 2024

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Incluce C++ libraries
#include <stdio.h>
#include <stdlib.h>
#include <string>

// Include required QT libraries
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication> 
#include <QProcess>         

// Include local classes
#include "MinesweeperLogic.h"
#include "CustomButton.h"

class MainWindow : public QMainWindow {
    Q_OBJECT    // Q_OBJECT tells QT compiler to allow class to use signals & slots

// Class methods & attributes 
public:
    // Constructors 
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // Method to handle the "Try Again" action (replay choice)
    void tryAgain();  

private:
    // QT Components 
    QWidget *centralWidget;
    QGridLayout *gridLayout;

    // Game Logic class object
    MinesweeperLogic *minesweeperLogic;         
    // Array of button Objects     
    CustomButton *buttons[MAX_ROWS][MAX_COLS];

    // Helper Routines
    void setupGrid();
    void handleButton(int row, int col, CustomButton *button);
    void revealCell(int row, int col, CustomButton *button);
    void revealCellAndNeighbors(int row, int col, CustomButton *button);
    void gameOver( bool winner );
};

#endif // MAINWINDOW_H
