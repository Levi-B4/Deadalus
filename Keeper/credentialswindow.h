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
    void RemoveCredential(int id);

private:
    Ui::CredentialsWindow *ui;

    // Array of rows of credentials
    QVector< QVector< QWidget* > > credentials;

    // QButtonGroup of buttons to remove a row
    QButtonGroup buttons;

    QGridLayout* layout;

    void LoadCredentials();

    // display credentials to gui
    void DisplayCredentials();

    void ConnectRemoveButton(QPushButton* button);

    void DecryptCredentials(QString keyPath);
};

#endif // CREDENTIALSWINDOW_H
