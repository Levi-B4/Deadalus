#ifndef CREDENTIALSTABLE_H
#define CREDENTIALSTABLE_H

#include <QWidget>

namespace Ui {
class Logins;
}

class Logins : public QWidget
{
    Q_OBJECT

public:
    explicit Logins(QWidget *parent = nullptr);
    ~Logins();

private:
    Ui::Logins *ui;
};

#endif // CREDENTIALSTABLE_H
