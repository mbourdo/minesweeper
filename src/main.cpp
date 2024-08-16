// Author: Michelle Bourdon   (Student ID: 251223429)
// Description: Main application launcher for the Minesweeper game.
//              Creates and shows the main window in a loop until the user chooses to exit.
// Date: Feb 6, 2024

#include <QApplication>
#include "MainWindow.h"

// Constants for result options
#define EXIT    0
#define REPLAY  1

// Main application launcher method
// Parameters:
//   - argc: Number of command line arguments
//   - argv: Pointer to Array of command line arguments
int main(int argc, char *argv[]) {
    int result = REPLAY;

    // Loop until user chooses to EXIT
    while (result == REPLAY) {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        result = a.exec();
    } 
    return result;
}
