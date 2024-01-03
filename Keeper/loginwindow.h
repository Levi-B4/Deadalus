#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "credentialswindow.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QVector>

#include <QGridLayout>

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
    // select source location
    void HandleSourceFileExplore();

    // select key location
    void HandleKeyFileExplore();

    // create new key and credentials
    void HandleNewCredentials();

    // read key and decrypt login credentials
    void HandleSubmitPressed();

private:
    // login window ui
    Ui::LoginWindow *ui;

    // central widget
    QWidget* centralWidget;

    // layout for the ui
    QVBoxLayout* layout;

    // array of QWidgets, grouped by section of ui
    QVector<QWidget*> sourceFileWidgets;
    QVector<QWidget*> keyFileWidgets;
    QVector<QWidget*> submissionWidgets;

    // window to display credentials
    CredentialsWindow* credentials;

    // displays ui
    void DisplayUI();

    // connects signals and slots for login window
    void ConnectSlots();

    // verifies new file creation
    bool CreateFile(QString FilePath);
};
#endif // LOGINWINDOW_H
