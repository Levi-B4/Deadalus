#include "test.h"
#include "ui_test.h"

#include <QGridLayout>
#include <QPushButton>

Test::Test(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Test)
{
    ui->setupUi(this);

    layout = new QGridLayout(this);

    layout->addWidget(new QPushButton("works?"), 0, 0);
}

Test::~Test()
{
    delete ui;
}
