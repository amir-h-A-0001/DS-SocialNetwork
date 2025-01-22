#ifndef LOGIN_SIGNUP_H
#define LOGIN_SIGNUP_H

#include <QMainWindow>
#include <QPropertyAnimation>

namespace Ui {
class Login_SignUp;
}

class Login_SignUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login_SignUp(QWidget *parent = nullptr);
    ~Login_SignUp();

    void setFramesShadow ();



private slots :
    void animation ();

private:
    Ui::Login_SignUp *ui;
};

#endif // LOGIN_SIGNUP_H
