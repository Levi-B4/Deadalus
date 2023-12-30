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

    // creates credentials window passing the file path
    credentials = new CredentialsWindow(ui->filePath->toPlainText());
    credentials->show();

    // closes login window
    close();
}

// connects signals and slots for window
void LoginWindow::ConnectSlots(){
    // connects file select button to its handler
    connect(
        // object emitting signal
        ui->fileSelectButton,
        // signal type
        &QPushButton::clicked,
        // object which owns slot
        this,
        // slot recieving signal
        &LoginWindow::HandleFileSelectionButtonPressed
    );

    // connects the createCredentials button to its handler
    connect(
        // object emitting signal
        ui->resetCredentialsButton,
        // signal type
        &QPushButton::clicked,
        // object which owns slot
        this,
        // slot recieving signal
        &LoginWindow::HandleResetCredentialsButtonPressed
        );

    // connects the submit button to its handler
    connect(
        // object emitting signal
        ui->submitButton,
        // signal type
        &QPushButton::clicked,
        // object which owns slot
        this,
        // slot recieving signal
        &LoginWindow::HandleSubmitKeyPressed
    );
}
