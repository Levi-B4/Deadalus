#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // create application
    QApplication app(argc, argv);

    // create login window
    LoginWindow w;

    // display login window
    w.show();

    // execute application logic
    return app.exec();
}
