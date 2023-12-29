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
            credentials[i].push_back(new QLineEdit());
            qobject_cast<QLineEdit*>(credentials[i][j])->setText("W/U/S");
        }
        buttons.addButton(new QPushButton("-"), i);
        layout->addWidget(buttons.button(i), i, 3);
        ConnectRemoveButton(qobject_cast<QPushButton*>(buttons.button(i)));
    }
    buttons.addButton(new QPushButton("+"), -2);
    layout->addWidget(buttons.button(-2), credentials.size(), 0, 1, 4);

    // display credentials starting at the first element
    DisplayCredentials(0);

    connect(
        buttons.button(-2),
        &QPushButton::clicked,
        this,
        &CredentialsWindow::AddCredential
    );
}

void CredentialsWindow::DisplayCredentials(int startingIndex){
    for(int i = startingIndex; i < credentials.size(); i++){
        for(int j = 0; j < credentials[0].size(); j++){
            layout->addWidget(credentials[i][j], i, j);
        }
    }
}

void CredentialsWindow::ConnectRemoveButton(QPushButton* button){
    connect(
        button,
        &QPushButton::clicked,
        this,
        &CredentialsWindow::RemoveCredential
    );
}

void CredentialsWindow::AddCredential(){

    QVector<QWidget*> row;

    for(int i = 0; i < 3; i++){
        row.push_back(new QLineEdit());
    }

    layout->removeWidget(buttons.button(-2));

    buttons.addButton(new QPushButton("-"), credentials.size());
    layout->addWidget(buttons.button(credentials.size()), credentials.size(), 3);
    ConnectRemoveButton(qobject_cast<QPushButton*>(buttons.button(credentials.size())));

    credentials.push_back(row);

    DisplayCredentials(credentials.size() - 1);

    layout->addWidget(buttons.button(-2), credentials.size() + 1, 0, 1, 4);
}

void CredentialsWindow::RemoveCredential(){
    std::cout << "removal pressed" << std::endl;

    // identify button pressed
    QObject* senderButton = sender();
    QPushButton* button = qobject_cast<QPushButton*>(senderButton);

    // get id of button pressed
    int id = buttons.id(button);

    // remove row from layout
    for(QWidget* widget : qAsConst(credentials[id])){
        layout->removeWidget(widget);
        delete widget;
    }
    // remove row from credentials vector
    credentials.remove(id);

    // remove following rows credentials from layout
    for(int i = id; i < credentials.size(); i++){
        for(QWidget* credentialEntry : qAsConst(credentials[i])){
            layout->removeWidget(credentialEntry);
        }
    }

    // identify last remove button
    QPushButton* buttonToDelete = qobject_cast<QPushButton*>(buttons.button(credentials.size()));

    // remove last button from layout
    layout->removeWidget(buttonToDelete);
    // remove last button from button group
    buttons.removeButton(buttonToDelete);
    // delete removed button
    delete buttonToDelete;

    // display credentials that have been temporarily removed
    DisplayCredentials(id);
}

void CredentialsWindow::DecryptCredentials(QString keyPath){
    CipherTool myCipher(keyPath.toStdString());

    // for each line in source file
        // decrypt line and write to table
}
