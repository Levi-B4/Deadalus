#include "credentialswindow.h"
#include "ui_credentialswindow.h"

#include "CipherTool/CipherTool.h"

#include <iostream>

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QWidget>
#include <QTableWidget>

CredentialsWindow::CredentialsWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CredentialsWindow)
{
    ui->setupUi(this);

    layout = new QGridLayout(this);

    LoadCredentials();

    // clear readable resource file
}

CredentialsWindow::~CredentialsWindow()
{
    delete ui;

    delete layout;
}

// display credentials from readable resource file
void CredentialsWindow::LoadCredentials(){
    // list current credentials
    // change i < 5 to resourceFile.hasNextLine()
    for(int i = 0; i < 5; i++){
        // create vector of row and add to credential array
        QVector<QWidget*> row;
        credentials.push_back(row);

        // iterate through line and add credentials as line edit
        for(int j = 0; j < 3; j++){
            credentials[i].push_back(new QLineEdit("Web,User,Pass"));
            layout->addWidget(credentials[i][j], i, j);
        }
        buttons.addButton(new QPushButton("-"), i);
        layout->addWidget(buttons.button(i), i, 3);
    }
    buttons.addButton(new QPushButton("+"), -2);
    layout->addWidget(buttons.button(-2), credentials.size(), 0, 1, 4);

    connect(
        buttons.button(-2),
        &QPushButton::clicked,
        this,
        &CredentialsWindow::AddCredential
    );
}

void CredentialsWindow::ConnectRemoveButton(QPushButton* button){
    connect(
        button,
        &QPushButton::clicked,
        this,
        &CredentialsWindow::AddCredential
    );
}

void CredentialsWindow::AddCredential(){

    QVector<QWidget*> row;
    for(int i = 0; i < 3; i++){
        row.push_back(new QLineEdit());
        layout->addWidget(row[i], credentials.size(), i);
    }

    credentials.push_back(row);

    buttons.addButton(new QPushButton("-"), credentials.size() - 1);
    layout->addWidget(buttons.button(credentials.size() - 1), credentials.size() - 1, 3);


    layout->addWidget(buttons.button(-2), credentials.size(), 0, 1, 4);
}

void CredentialsWindow::RemoveCredential(int id){

}

void CredentialsWindow::DecryptCredentials(QString keyPath){
    CipherTool myCipher(keyPath.toStdString());

    // for each line in source file
        // decrypt line and write to table
}
