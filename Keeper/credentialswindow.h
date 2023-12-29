#ifndef CREDENTIALSWINDOW_H
#define CREDENTIALSWINDOW_H

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
    // add row for credentials to list
    void AddCredential();

    // remove row from list
    void RemoveCredential();

private:
    Ui::CredentialsWindow *ui;

    // Array of rows of credentials
    QVector< QVector< QWidget* > > credentials;

    // QButtonGroup of buttons to remove a row
    QButtonGroup buttons;

    // layout for the window
    QGridLayout* layout;

    // loads saved credentials and displays buttons
    void LoadCredentials();

    // display credentials to gui
    void DisplayCredentials(int startingIndex);

    // connects a button to the RemoveCredential slot
    void ConnectRemoveButton(QPushButton* button);

// may remove as it is redundant of CipherTool class
    void DecryptCredentials(QString keyPath);
};

#endif // CREDENTIALSWINDOW_H
