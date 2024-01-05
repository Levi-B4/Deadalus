#include "credentialswindow.h"
#include "ui_credentialswindow.h"

#include "CipherTool/CipherTool.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

#include <QString>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QButtonGroup>
#include <QWidget>
#include <QTableWidget>
#include <QLabel>

CredentialsWindow::CredentialsWindow(QString sourcePath, QString keyPath, bool isNewCredentials)
    : ui(new Ui::CredentialsWindow)
{
    // creates window ui
    ui->setupUi(this);

    setWindowTitle("Keyper Credentials");

    // creates cipher tool, passing in key path
    cipher = new CipherTool(keyPath.toStdString());

    // set source file path
    this->sourcePath = sourcePath;

    // creates a new key inside keyPath file
    if(isNewCredentials){
        cipher->CreateNewKey();
    }

    // create window layout as a grid
    layout = new QGridLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setVerticalSpacing(5);

    // load credentials from resource file
    LoadCredentials();

    // chart labels
    QVector<QLabel*> tempLabelVector;
    tempLabelVector.push_back(new QLabel("Website"));
    tempLabelVector.push_back(new QLabel("Username"));
    tempLabelVector.push_back(new QLabel("Password"));

    for(int i = 0; i < tempLabelVector.size(); i++){
        tempLabelVector[i]->setMaximumHeight(30);
        layout->addWidget(tempLabelVector[i], 0, i);
    }
}

CredentialsWindow::~CredentialsWindow()
{
    // delete ui and layout
    delete ui;
    delete layout;

    // delete cipher tool
    delete cipher;

    // delete "+" button
    delete buttons.button(-1);

    // delete all "-" buttons
    for(int i = -1; i < credentials.size(); i++){
        delete buttons.button(i);
    }

    // delete all credential LineEdits
    for(QVector<QLineEdit*> row : qAsConst(credentials)){
        for(QLineEdit* lineEdit : qAsConst(row)){
            delete lineEdit;
        }
    }
}

// add row for credentials to ui
void CredentialsWindow::AddCredential(){

    // create vector to hold row widgets
    QVector<QLineEdit*> row;

    // add widgets to row vector
    for(int i = 0; i < 3; i++){
        row.push_back(new QLineEdit());
    }

    // add new "-" button to and add on click function for row removal
    buttons.addButton(new QPushButton("-"), credentials.size());
    ConnectRemoveButton(qobject_cast<QPushButton*>(buttons.button(credentials.size())));

    // display remove button
    layout->addWidget(buttons.button(credentials.size()), credentials.size() + 1, 3);

    // add row to credentials vector
    credentials.push_back(row);

    DisplayCredentials(credentials.size() - 1);
}

// removes a row
void CredentialsWindow::RemoveRow(){
    // identify button pressed
    QObject* senderButton = sender();
    QPushButton* button = qobject_cast<QPushButton*>(senderButton);

    // get id of button pressed
    int id = buttons.id(button);

    // remove row from layout
    for(QLineEdit* lineEdit : qAsConst(credentials[id])){
        layout->removeWidget(lineEdit);
        delete lineEdit;
    }
    // remove row from credentials vector
    credentials.remove(id);

    // identify last remove button
    QPushButton* buttonToDelete = qobject_cast<QPushButton*>(buttons.button(credentials.size()));

    // remove last remove button from layout
    layout->removeWidget(buttonToDelete);
    // remove last remove button from button group
    buttons.removeButton(buttonToDelete);
    // delete removed button
    delete buttonToDelete;

    // display credentials that have been temporarily removed
    DisplayCredentials(id);
}

// saves all credentials to source file, encoded with cipher and key file
void CredentialsWindow::Save(){
    QFile sourceFile(sourcePath);

    if(sourceFile.open(QIODevice::ReadWrite)){
        QTextStream stream(&sourceFile);
        stream << QString::fromStdString(cipher->Encode(credentials[0][0]->text().toStdString()));
    }

    sourceFile.close();
}

// load and display credentials from resource file
void CredentialsWindow::LoadCredentials(){
    // change i < 5 to resourceFile.hasNextLine()
    for(int i = 0; i < 5; i++){
        // create vector of row and add to credential array
        QVector<QLineEdit*> row;
        credentials.push_back(row);

        // iterate through line and add credentials to row as line edits
        for(int j = 0; j < 3; j++){
            credentials[i].push_back(new QLineEdit());
            credentials[i][j]->setText("W/U/S");
        }

        // create button to remove row on click
        buttons.addButton(new QPushButton("-"), i);
        layout->addWidget(buttons.button(i), i + 1, 3);

        // implement onlick for "-" buttons
        ConnectRemoveButton(qobject_cast<QPushButton*>(buttons.button(i)));
    }

    QFile sourceFile(sourcePath);

    if(!sourceFile.open(QIODevice::ReadOnly)){
        QMessageBox::critical(
            this,
            tr("Keyper"),
            tr("Could not open source file!")
        );
    } else{
        QTextStream in(&sourceFile);

        while(!in.atEnd()){
            QString line = in.readLine();
            //QStringList fields = line.split(",");
            credentials[0][0]->setText(QString::fromStdString(cipher->Decode(line.toStdString())));
        }
    }

    // create button for adding rows
    buttons.addButton(new QPushButton("+"), -1);
    layout->addWidget(buttons.button(-1), credentials.size(), 0, 1, 4);

    // implement onlick for "+" button
    connect(
        buttons.button(-1),
        &QPushButton::clicked,
        this,
        &CredentialsWindow::AddCredential
    );

    // create button for saving credentials to file
    buttons.addButton(new QPushButton("Save"), -2);

    // implement saving for "Save" button
    connect(
        buttons.button(-2),
        &QPushButton::clicked,
        this,
        &CredentialsWindow::Save
    );

    // create button for clearing all credentials
    buttons.addButton(new QPushButton("Clear"), -3);

    // implement clearing for "clear" button
    // connect();

    // display credentials starting at the first row
    DisplayCredentials(0);
}

// display credentials - param: int startingIndex
void CredentialsWindow::DisplayCredentials(int startingIndex){
    // iterate through each row starting at startingIndex and add them to the layout
    for(int i = startingIndex; i < credentials.size(); i++){
        for(int j = 0; j < credentials[0].size(); j++){
            layout->addWidget(credentials[i][j], i + 1, j);
        }
    }

    layout->removeWidget(buttons.button(-1));
    layout->addWidget(buttons.button(-1), credentials.size() + 1, 0, 1, 4);

    for(int i = -2; buttons.button(i) != nullptr; i--){
        layout->removeWidget(buttons.button(i));
        layout->addWidget(buttons.button(i), credentials.size() + 2, (i * -1) - 2);
    }

}

// connects a button to the RemoveCredential slot
void CredentialsWindow::ConnectRemoveButton(QPushButton* button){
    connect(
        button,
        &QPushButton::clicked,
        this,
        &CredentialsWindow::RemoveRow
        );
}
