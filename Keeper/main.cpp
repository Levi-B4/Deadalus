#include "loginwindow.h"
#include "credentialswindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // create application
    QApplication app(argc, argv);

    // create login window
    LoginWindow login;
//    CredentialsWindow credentials;

    // display login window
    login.show();
    //credentials.show();

    // execute application logic
    return app.exec();
}
