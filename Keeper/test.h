#ifndef TEST_H
#define TEST_H

#include <QWidget>

#include <QGridLayout>

namespace Ui {
class Test;
}

class Test : public QWidget
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();

private:
    Ui::Test *ui;

    QGridLayout* layout;
};

#endif // TEST_H
