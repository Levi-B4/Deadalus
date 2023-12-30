#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "credentialswindow.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    // allows for the use of slots and signals
    Q_OBJECT

public:
    // constructor - parameters: QWidget* parent = nullptr
    LoginWindow(QWidget *parent = nullptr);

    // default destructor
    ~LoginWindow();

public slots:
    // select key location
    void HandleFileSelectionButtonPressed();

    // create new key and credentials
    void HandleResetCredentialsButtonPressed();

    // read key and decrypt login credentials
    void HandleSubmitKeyPressed();

private:
    // pointer to window ui
    Ui::LoginWindow *ui;

    CredentialsWindow* credentials;

    // connects signals and slots for login window
    void ConnectSlots();
};
#endif // LOGINWINDOW_H
