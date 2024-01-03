#include "loginwindow.h"
#include "./ui_loginwindow.h"

#include "credentialswindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QInputDialog>
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

    setWindowTitle("Keyper Login");

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

void LoginWindow::HandleNewCredentials(){
    // create dialog for selecting a directory
    QFileDialog selectDirectory;
    selectDirectory.setFileMode(QFileDialog::Directory);
    selectDirectory.setOption(QFileDialog::ShowDirsOnly);
    selectDirectory.setWindowTitle("Select Target Directory");

    // get a directory for creating the new source and key files
    QString targetDirectory = selectDirectory.getExistingDirectory(this);

    // get input for source file name
    QString sourceNameInput = QInputDialog::getText(this,"New Source File Name","Name the new Source File: ");
    QString sourcePath= targetDirectory + "/" + sourceNameInput;

    // create source file and return if file can't be created
    if(!CreateFile(sourcePath)){
        return;
    }

    // get input for key file name
    QString keyNameInput = QInputDialog::getText(this,"New Key File Name","Name the new Key File: ");
    QString keyPath = targetDirectory + "/" + keyNameInput;

    // create source file and return if file can't be created
    if(!CreateFile(keyPath)){
        return;
    }

    // creates credentials window passing the file path
    credentials = new CredentialsWindow(sourcePath, keyPath);

    credentials->show();

    // hides login window
    close();
}

// read key and decrypt login credentials
void LoginWindow::HandleSubmitPressed(){
    if(qobject_cast<QLineEdit*>(sourceFileWidgets[1])->displayText() == ""
        || qobject_cast<QLineEdit*>(keyFileWidgets[1])->displayText() == ""){
        return;
    }

    // creates credentials window passing the source path and key path
    credentials = new CredentialsWindow(
        qobject_cast<QLineEdit*>(sourceFileWidgets[1])->displayText(),
        qobject_cast<QLineEdit*>(keyFileWidgets[1])->displayText()
    );
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

    submissionWidgets.push_back(new QPushButton("New Credentials"));
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

    // cennects the new credentials button to its handler
    connect(
        // object emitting signal
        qobject_cast<QPushButton*>(submissionWidgets[0]),
        // signal type
        &QPushButton::clicked,
        // object which owns slot
        this,
        // slot recieving signal
        &LoginWindow::HandleNewCredentials
    );

    // connects the submit button to its handler
    connect(
        // object emitting signal
        qobject_cast<QPushButton*>(submissionWidgets[1]),
        // signal type
        &QPushButton::clicked,
        // object which owns slot
        this,
        // slot recieving signal
        &LoginWindow::HandleSubmitPressed
    );
}

// checks if file can be created, prompting user for input if file will be overwritten
bool LoginWindow::CreateFile(QString filePath){
    //
    QFile newFile(filePath);

    if(newFile.exists()){
        // create message box
        QMessageBox fileExistsMessage(this);

        // create message ui
        fileExistsMessage.setText("This file already exists, would you like to overwrite it?");

        fileExistsMessage.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        switch(fileExistsMessage.exec()){
            case QMessageBox::YesRole:
                newFile.resize(0);
                break;

            case QMessageBox::NoRole:
                return false;
                break;
        }
    }

    if(newFile.open(QIODevice::ReadOnly)){
        newFile.close();
        return true;
    } else {
        QMessageBox cannotCreateFileMessage(this);
        cannotCreateFileMessage.setText("File cannot be created, create it manually then try again");

        cannotCreateFileMessage.setStandardButtons(QMessageBox::Ok);
        cannotCreateFileMessage.exec();
        return false;
    }
}
