#include "loginwindow.h"
#include "./ui_loginwindow.h"

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

// read key and decrypt login credentials
void LoginWindow::HandleSubmitKeyPressed(){

}

// connects signals and slots for window
void LoginWindow::ConnectSlots(){
    // connects the submit button to the HandleSubmitKeyPressed function
    connect(
        // object emitting signal
        ui->submitButton,
        // signal type
        SIGNAL(click()),
        // object which owns slot
        this,
        // slot recieving signal
        SLOT(HandleSubmitKeyPressed())
    );


}
