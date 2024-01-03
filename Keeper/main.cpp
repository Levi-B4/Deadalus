#include "loginwindow.h"
#include "credentialswindow.h"
#include "test.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // create application
    QApplication app(argc, argv);

    // create login window
    LoginWindow login;
    CredentialsWindow credentials("test");
    Test test;

    // display login window
    login.show();
    //credentials.show();
    //test.show();

    // execute application logic
    return app.exec();
}
