#include "loginwindow.h"
#include "./ui_loginwindow.h"

#include "credentialswindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QGridLayout>

// constructor - parameters: QWidget* parent = nullptr
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    // creates ui object
    ui->setupUi(this);

    // create central widget
    //(main window must use a central widget for its layout)
    centralWidget = new QWidget();
    setCentralWidget(centralWidget);

    // create window layout
    layout = new QVBoxLayout();
    centralWidget->setLayout(layout);

    // display ui
    DisplayUI();

    // connects signals and slots for window
    ConnectSlots();
}

// default destructor
LoginWindow::~LoginWindow()
{
    // delete ui pointer
    delete ui;

    // delete layout
    delete layout;
}

void LoginWindow::HandleSourceFileExplore(){
    QString path = QFileDialog::getOpenFileName(this, tr("Source Location"));
    if(path.isNull() == false){
        qobject_cast<QLineEdit*>(sourceFileWidgets[1])->insert(path);
    }
}

void LoginWindow::HandleKeyFileExplore(){
    QString path = QFileDialog::getOpenFileName(this, tr("Key Location"));
    if(path.isNull() == false){
        qobject_cast<QLineEdit*>(keyFileWidgets[1])->insert(path);
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
    if(qobject_cast<QLineEdit*>(sourceFileWidgets[1])->displayText() == ""
        || qobject_cast<QLineEdit*>(keyFileWidgets[1])->displayText() == ""){
        return;
    }

    // creates credentials window passing the file path
    credentials = new CredentialsWindow(qobject_cast<QLineEdit*>(sourceFileWidgets[1])->displayText());
    credentials->show();

    // hides login window
    close();
}

// displays ui
void LoginWindow::DisplayUI(){
    // create widgets for source file
    sourceFileWidgets.push_back(new QLabel("Source File: "));
    sourceFileWidgets.push_back(new QLineEdit());
    sourceFileWidgets.push_back(new QPushButton("Explore..."));centralWidget;

    // add source file widgets to layout
    QHBoxLayout* sourceLayout = new QHBoxLayout(this);
    for(QWidget* widget : qAsConst(sourceFileWidgets)){
        sourceLayout->addWidget(widget);
    }
    layout->addLayout(sourceLayout);

    // create widgets for key file
    keyFileWidgets.push_back(new QLabel("Key File: "));
    keyFileWidgets.push_back(new QLineEdit());
    keyFileWidgets.push_back(new QPushButton("Explore..."));

    // add key file widgets to layout
    QHBoxLayout* keyLayout = new QHBoxLayout(this);
    for(QWidget* widget : qAsConst(keyFileWidgets)){
        keyLayout->addWidget(widget);
    }
    layout->addLayout(keyLayout);

    submissionWidgets.push_back(new QPushButton("submit"));
    // add submission widgets to layout
    QHBoxLayout* submissionLayout = new QHBoxLayout(this);
    for(QWidget* widget : qAsConst(submissionWidgets)){
        submissionLayout->addWidget(widget);
    }
    layout->addLayout(submissionLayout);
}

// connects signals and slots for window
void LoginWindow::ConnectSlots(){
    // connects source explore button to its handler
    connect(
        // object emitting signal - source file explore button
        qobject_cast<QPushButton*>(sourceFileWidgets[2]),
        // signal type
        &QPushButton::clicked,
        // object which owns slot
        this,
        // slot recieving signal
        &LoginWindow::HandleSourceFileExplore
    );

    // connects key explore button to its handler
    connect(
        // object emitting signal - source file explore button
        qobject_cast<QPushButton*>(keyFileWidgets[2]),
        // signal type
        &QPushButton::clicked,
        // object which owns slot
        this,
        // slot recieving signal
        &LoginWindow::HandleKeyFileExplore
    );

    //crashes, something with the signal or emitter i think
    // connects the submit button to its handler
    connect(
        // object emitting signal
        qobject_cast<QPushButton*>(submissionWidgets[0]),
        // signal type
        &QPushButton::clicked,
        // object which owns slot
        this,
        // slot recieving signal
        &LoginWindow::HandleSubmitKeyPressed
    );
}
