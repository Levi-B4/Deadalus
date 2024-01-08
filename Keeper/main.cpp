#include "loginwindow.h"
#include "credentialswindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // create application
    QApplication app(argc, argv);

    // create login window
    LoginWindow login;

    // display login window
    login.show();


    // execute application logic
    return app.exec();
}
