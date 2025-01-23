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


private slots :
    // Animation slot
    void animation ();

private:
    // Set Shadows for frames
    void setFramesShadow ();

    // Check Errors for Login
    bool checkAllLoginErrors ();
    bool checkUsernameLoginError ();
    bool checkPasswordLoginError ();

    // Check Errors for Signup
    bool checkAllSignupErrors ();
    bool checkUsernameSignupError ();
    bool checkPasswordSignupError ();

    Ui::Login_SignUp *ui;
};

#endif // LOGIN_SIGNUP_H
