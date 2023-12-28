#include "loginwindow.h"
#include "./ui_loginwindow.h"

#include "credentialswindow.h"

#include <QFileDialog>
#include <QMessageBox>

// constructor - parameters: QWidget* parent = nullptr
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    // creates ui object
    ui->setupUi(this);

    // connects signals and slots for window
    ConnectSlots();
}

// default destructor
LoginWindow::~LoginWindow()
{
    // delete ui pointer
    delete ui;
}

void LoginWindow::HandleFileSelectionButtonPressed(){
    QString path = QFileDialog::getOpenFileName(this, tr("Key Location"));
    if(path.isNull() == false){
        ui->filePath->setPlainText(path);
    }
}

void LoginWindow::HandleResetCredentialsButtonPressed(){
    QMessageBox resetWarning;
    resetWarning.setText("This will delete any currently saved credentials");
    resetWarning.setInformativeText("Would you like to continue?");
    resetWarning.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);

    switch(resetWarning.exec()){
        case QMessageBox::Ok:

            break;
        case QMessageBox::Cancel:

            break;
        default:
            // should not be reached
            break;
    }

    // decrypt encrypted resource file to readable resource file

    // show credentials
}

// read key and decrypt login credentials
void LoginWindow::HandleSubmitKeyPressed(){
    if(ui->filePath->document()->isEmpty()){
        return;
    }

    // display credential window passing key path
}

// connects signals and slots for window
void LoginWindow::ConnectSlots(){

    // connects the
    connect(
        // object emitting signal
        ui->fileSelectButton,
        // signal type
        SIGNAL(clicked()),
        // object which owns slot
        this,
        // slot recieving signal
        SLOT(HandleFileSelectionButtonPressed())
    );

    // connects the createCredentials button to the HandleCredentialsButtonPressed function
    connect(
        // object emitting signal
        ui->resetCredentialsButton,
        // signal type
        SIGNAL(clicked()),
        // object which owns slot
        this,
        // slot recieving signal
        SLOT(HandleResetCredentialsButtonPressed())
        );

    // connects the submit button to the HandleSubmitKeyPressed function
    connect(
        // object emitting signal
        ui->submitButton,
        // signal type
        SIGNAL(clicked()),
        // object which owns slot
        this,
        // slot recieving signal
        SLOT(HandleSubmitKeyPressed())
    );
}
