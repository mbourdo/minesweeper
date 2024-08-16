// Author: Michelle Bourdon   (Student ID: 251223429)
// Description: Implementation of the CustomButton class for the Minesweeper game.
//              This class extends QPushButton and adds custom features like handling
//              right-click events for flagging cells.
// Date: Feb 6, 2024

// Include the corresponding header file
#include "CustomButton.h"

// Function: CustomButton   (Constructor)
// Parameters:
//   - row: Row position of the button on the Minesweeper grid
//   - col: Column position of the button on the Minesweeper grid
//   - parent: Parent widget (default is nullptr)
CustomButton::CustomButton(int row, int col, QWidget *parent)
    : QPushButton(parent), row(row), col(col) {

    // Set internal variables
    this->row = row;
    this->col = col;
    this->flagStatus = 0;

    // Customize button appearance
    // Set button and icon size
    this->setFixedSize (BUTTON_SIZE, BUTTON_SIZE);            
    this->setIconSize(QSize(ICON_SIZE, ICON_SIZE));

    // Set policy for buttons when hidden
    QSizePolicy sp_retain = this->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    this->setSizePolicy(sp_retain);

    // Connect Method for "clicked" signal
    connect(this, &CustomButton::mouseRight, this, [=](){ this->handleRight();} );
}

// Function: ~CustomButton   (Destructor)
// Description: Cleanup resources 
CustomButton::~CustomButton() {
    // Cleanup resources
}

// Function: getRow 
// Description: get the row value of the cell
// Returns:
//   - Integer representing the row position
int CustomButton::getRow() const {
    return row;
}

// Function: getCol
// Description: get the column value of the cell
// Returns:
//   - Integer representing the column position
int CustomButton::getCol() const {
    return col;
}

// Function: handleRight
// Description: Handle right-click event (used for flagging cells)
void CustomButton::handleRight() {
    qDebug() << "Right click at row:" << this->getRow() << "col:" << this->getCol();   
    this->flagStatus = (this->flagStatus +1) % FLAG_VALUES;    // Add one to flag state and wrap 
    setButtonIcon();
}

// Function: mouseReleaseEvent
// Description: Override mouseReleaseEvent to handle right-click and emit custom signal
// Parameters:
//   - e: QMouseEvent containing information about the mouse event
void CustomButton::mouseReleaseEvent(QMouseEvent *e) {
    if (e->button() == Qt::RightButton) emit mouseRight();
    else if (e->button() == Qt::LeftButton) emit clicked();
}

// Function: setButtonIcon
// Description: Set the button Icon 
//          Note that we use a combination of no icon, mine flag icon, and text "?"
//          When using an icon, we clear the text, and vice versa
void CustomButton::setButtonIcon() {
    switch (flagStatus) {
        case NOFLAG:
            this->setText( "" );
            this->setIcon(QIcon());
            break;
        case FLAGGED:
            this->setText( "" );
            this->setIcon(QIcon("icons/mine_flag.png"));
            break;
        case QUESTION:
            this->setIcon(QIcon());
            this->setText( "?" );
            break;
    }  
}
