// Author: Michelle Bourdon   (Student ID: 251223429)
// Description: Implementation of the MainWindow class for the Minesweeper game.
//              This class represents the Qt-based user interface of the Minesweeper
//              application, including setup of all Qt comoponents, and changes to them.
// Date: Feb 6, 2024

#include "MainWindow.h"
#include "CustomButton.h"

// Function: MainWindow   (constructor)
// Description: Initializes the main window for the Minesweeper game.
//              Sets up the title, central widget, grid layout, and QPushButtons
// Parameters:
//   - parent: Pointer to the parent widget (default is nullptr).
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Set Main WIndow Title
    this->setWindowTitle("Minesweeper");

    // Add a main widget
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a gridLayout object (with no spacing) for PushButtons
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(0);

    // Create Game Logic CLass objects
    minesweeperLogic = new MinesweeperLogic();

    // Setup the Board UI Grid 
    setupGrid();
}

// Function: ~MainWindow
// Description: Destructor for the MainWindow class. Deletes the MinesweeperLogic object.
MainWindow::~MainWindow() {
    delete minesweeperLogic;  // Object created in constructor
}

// Function: tryAgain
// Description: // Method for user signal they want to play again
void MainWindow::tryAgain() {
    // Restart applcation - return (1) as signal to main()
    QCoreApplication::exit(1);
}

// Function: setupGame
// Description: Creates CustomButton objects for each cell in the Minesweeper UI grid.
//              Connects the clicked signal to the handleButton method.
//              Initializes the game board and layout.
void MainWindow::setupGrid() {
    // Loop over board and create QPushButton objects
    for (int row = 0; row < minesweeperLogic->rows; ++row) {
        for (int col = 0; col < minesweeperLogic->cols; ++col) {
            // Create Custom Push Button 
            CustomButton *button = new CustomButton(row, col, this);

            // Connect Method for "clicked" signal to handleButton method (in mainwindow)
            // Calls the specific button-> getRow and getCol methods to pass the button position
            connect(button, &CustomButton::clicked, 
               [this, button]() { handleButton(button->getRow(), button->getCol(), button);} ); 

            // Add Custom Push Button to the gridLayout
            gridLayout->addWidget(button, row, col);

            // Keep references to the button objects (for methods that access multiple buttons)
            buttons[row][col] = button; 
        }
    }
}

// Function: handleButton
// Description: Handles the button click event by checking for game end conditions,
//              revealing cells, and checking for a win or loss.
// Parameters:
//   - row: Row position of the clicked button.
//   - col: Column position of the clicked button.
//   - button: Pointer to the clicked CustomButton object.
void MainWindow::handleButton(int row, int col, CustomButton *button) {
    // Check for a cell being clicked twice - do not process these
    if ( minesweeperLogic->isClicked(row, col) == true) {
        // TESTING - For double clicked cells
        qDebug() << "Button *already* clicked at row:" << row << "col:" << col;
        return;
    }

    // TESTING - Print moves made and specific buttons clicked
    qDebug() << "Moves made: " << minesweeperLogic->getMoves()+1 << "out of: " << minesweeperLogic->winMoves;
    qDebug() << "Button clicked at row:" << row << "col:" << col;

    // Check for End of Game (bomb hit or max moves)
    if (minesweeperLogic->isBomb(row, col)) {
        qDebug() << "Game Over! Bomb exploded at row:" << row << "col:" << col;
        // Reveal the final cell
        minesweeperLogic->addMove();            // Increment # of moves played
        minesweeperLogic->setClicked(row, col); // Mark cell as clicked
        revealCell(row, col, button);           // Reveal button
        gameOver( false );                      // false is loose
    }
    else if ( minesweeperLogic->getMoves()+1 == minesweeperLogic->winMoves  ) {
        qDebug() << "YOU WIN!";
        // Reveal the final cell
        minesweeperLogic->addMove();            // Increment # of moves played
        minesweeperLogic->setClicked(row, col); // Mark cell as clicked
        revealCell(row, col, button);           // Reveal button
        gameOver( true );                       // true is win   
    }
    else {
        // check neighbors and show values
        revealCellAndNeighbors(row, col, button);

        // Check if last revealed cell was final move (nothing left to click)
        if ( minesweeperLogic->getMoves() == minesweeperLogic->winMoves  ) 
            gameOver( true );                  // true is win   
    }
    return;
}

// Function: revealCell
// Description: Reveals a cell by updating its display to text or icon based on the value
// Parameters:
//   - row: Row position of the cell to reveal.
//   - col: Column position of the cell to reveal.
//   - button: Pointer to the CustomButton object representing the cell.
void MainWindow::revealCell(int row, int col, CustomButton *button) {
    // Testing 
    // qDebug() << "Reveal cell at row:" << row << "col:" << col;
    int count = minesweeperLogic->getNeighborBombCount(row, col);
    if (count > 0) {   // non-zero count
        // Get the count as an integer
        int adjacentBombs = minesweeperLogic->getNeighborBombCount(row, col);
        char c [2];                 // Convert to a one character string
        snprintf(c, 2, "%d", adjacentBombs);
        button->setText( c );       // Write the string
    }
    else if (count == 0)  { // blank
        button->hide();
    }
    else {   // bomb
        button->setIcon( QIcon("icons/bomb_explode.png") );
    }
    return;
}


// Function: revealCellAndNeighbors
// Description: Recursively reveals the clicked cell and its neighbors based on Minesweeper rules.
//              (if blank) - including their blank neighbors
//              Method uses recursion. Base case is when the button is NOT blank
// Parameters:
//   - row: Row position of the clicked cell.
//   - col: Column position of the clicked cell.
//   - button: Pointer to the CustomButton object representing the clicked cell.
void MainWindow::revealCellAndNeighbors(int row, int col, CustomButton *button) {
    // Testing 
    qDebug() << "Reveal cell at row:" << row << "col:" << col;

    // Base case (button is not blank) - Reveal only this button and return
    if ( minesweeperLogic->getNeighborBombCount(row, col) > 0) {    
        minesweeperLogic->addMove();            // Increment # of moves played
        minesweeperLogic->setClicked(row, col); // Mark cell as clicked
        revealCell(row, col, button);           // Reveal button
        return;
    }

    // else - Blank cell case - reveal it, and then call with it's neighbors
    // Reveal this button
    minesweeperLogic->addMove();            // Increment # of moves played
    minesweeperLogic->setClicked(row, col); // Mark cell as clicked
    revealCell(row, col, button);           // Reveal button

    // Recursively reveal uncliked neighbors with zero neighboring bombs
    // Neighbors have row and columns values +1 or -1 from the current (row, col)
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            // Avoid going out of bounds
            if (newRow >= 0 && newRow < minesweeperLogic->rows &&
                newCol >= 0 && newCol < minesweeperLogic->cols) {
                // If neighbor not clicked call this method on it (recursion)
                if ( minesweeperLogic->isClicked(newRow, newCol) == false) {
                    // Recursively reveal the neighbor
                    revealCellAndNeighbors(newRow, newCol, buttons[newRow][newCol] );
                }
            }
        }
    }
    return;
}

// Function: gameOver
// Description: Displays a pop-up message box to inform the player of the game outcome (win or lose).
//              Provides options to try again or exit the game.
// Parameters:
//   - winner: Boolean indicating whether the game was won (true) or lost (false).
void MainWindow::gameOver( bool winner ) {
    // Create Message Popup for game over action
    QMessageBox msgBox(this);

    // Create custom buttons
    QPushButton* tryAgainButton = new QPushButton("Try Again");
    QPushButton* exitButton = new QPushButton("Exit");

    // Add custom buttons to the message box
    msgBox.addButton(tryAgainButton, QMessageBox::ActionRole);
    msgBox.addButton(exitButton, QMessageBox::ActionRole);

    // Set default button 
    msgBox.setDefaultButton(tryAgainButton);

    if (winner) {
        msgBox.setWindowTitle("Game Over");
        msgBox.setText("Congratulations! You win!");

        // msgBox.setIcon(QIcon("icons/bomb_explode.png"));
        msgBox.setIconPixmap(QPixmap("icons/bomb_explode_sm.png"));
    }
    else {  // lose
        msgBox.setWindowTitle("Game Over");
        msgBox.setText("Uh Oh! You hit a mine and exploded.");

        // msgBox.setIcon(QIcon("icons/bomb_explode.png"));
        msgBox.setIconPixmap(QPixmap("icons/bomb_explode_sm.png"));
    }

    // Show the pop-up window
    int choice = msgBox.exec();

    // Handle button choices
    if (choice == 0) {  //Try Again choice
        qDebug() << "User chose play again ";
        tryAgain();  // Call the custom slot to restart the application
    } else { // Exit choice
        qDebug() << "User chose exit";
        QCoreApplication::quit();  // Close the application            
    }
}
