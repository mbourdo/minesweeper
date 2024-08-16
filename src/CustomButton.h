// Author: Michelle Bourdon   (Student ID: 251223429)
// Description: Declaration of the CustomButton class for the Minesweeper game.
//              This class extends QPushButton and adds custom features like handling
//              right-click events for flagging cells.
// Date: Feb 6, 2024

#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

// Include required QT libraries
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QCoreApplication> 
#include <QProcess>         
#include <QMouseEvent>         

// Button Constants
#define BUTTON_SIZE     22
#define ICON_SIZE       18
#define FLAG_VALUES     3
#define NOFLAG          0
#define FLAGGED         1
#define QUESTION        2

// Class declaration for CustomButton
class CustomButton : public QPushButton {
    Q_OBJECT    // Q_OBJECT tells QT compiler to allow class to use signals & slots

// Class methods & attributes 
public:
    // Constructor 
    CustomButton(int row, int col, QWidget *parent = nullptr);
    ~CustomButton();
  
    // Get/set methods
    int getRow() const;
    int getCol() const;
    
public slots:
    // Slot to handle right-click event
    void handleRight();    

signals:
    // Signal emitted when the right mouse button is clicked
    void mouseRight();    

protected:
    // Override mouseReleaseEvent to handle right-mouse button releases
    void mouseReleaseEvent(QMouseEvent *e);

private:
    // position on grid
    int row;
    int col;
    int flagStatus;         // 0 = unflagged, 1 = flagged, 2 = question
    void setButtonIcon();   // Set the button icon based on the flag status
};

#endif // CUSTOMBUTTON_H
