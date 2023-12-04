#include "credentialsTable.h"
#include "ui_credentialsTable.h"

Logins::Logins(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Logins)
{
    ui->setupUi(this);
}

Logins::~Logins()
{
    delete ui;
}
