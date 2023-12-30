#ifndef CREDENTIALSWINDOW_H
#define CREDENTIALSWINDOW_H

#include "CipherTool/CipherTool.h"

#include <QWidget>
#include <QButtonGroup>
#include <QGridLayout>
#include <QPushButton>

namespace Ui {
class CredentialsWindow;
}

class CredentialsWindow : public QWidget
{
    // allows for the use of slots and signals
    Q_OBJECT

public:
    // constructor - parameters: QWidget* parent = nullptr
    explicit CredentialsWindow(QWidget *parent = nullptr);
    ~CredentialsWindow();

public slots:
    // add row for credentials to ui
    void AddCredential();

    // removes a row
    void RemoveRow();

private:
    // pointer to window ui
    Ui::CredentialsWindow *ui;

    // Array of rows of credentials
    QVector< QVector< QWidget* > > credentials;

    // QButtonGroup of buttons to remove a row
    QButtonGroup buttons;

    // layout for the window
    QGridLayout* layout;

    // cipher tool used to encode and decode data
    CipherTool* cipher;

    // load and display credentials from resource file
    void LoadCredentials();

    // display credentials - param: int startingIndex
    void DisplayCredentials(int startingIndex);

    // connects a button to the RemoveCredential slot
    void ConnectRemoveButton(QPushButton* button);
};

#endif // CREDENTIALSWINDOW_H
