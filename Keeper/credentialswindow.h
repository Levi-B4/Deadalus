#ifndef CREDENTIALSWINDOW_H
#define CREDENTIALSWINDOW_H

#include "CipherTool/CipherTool.h"

#include <QString>
#include <QWidget>
#include <QButtonGroup>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

namespace Ui {
class CredentialsWindow;
}

class CredentialsWindow : public QWidget
{
    // allows for the use of slots and signals
    Q_OBJECT

public:
    // constructor - parameters: QString filePath
    explicit CredentialsWindow(QString sourcePath, QString keyPath, bool IsNewCredentials = false);
    ~CredentialsWindow();

public slots:
    // add row for credentials to ui
    void AddCredential();

    // removes a row
    void RemoveRow();

    // saves all credentials to source file, encoded with cipher and key file
    void Save();

private:
    // pointer to window ui
    Ui::CredentialsWindow *ui;

    // Array of rows of credentials
    QVector< QVector< QLineEdit* > > credentials;

    // QButtonGroup of buttons to remove a row
    QButtonGroup buttons;

    // layout for the window
    QGridLayout* layout;

    // cipher tool used to encode and decode data
    CipherTool* cipher;

    // path to file containing source of credentials
    QString sourcePath;

    // load and display credentials from resource file
    void LoadCredentials();

    // display credentials - param: int startingIndex
    void DisplayCredentials(int startingIndex);

    // connects a button to the RemoveCredential slot
    void ConnectRemoveButton(QPushButton* button);
};

#endif // CREDENTIALSWINDOW_H
