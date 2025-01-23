#ifndef LOGIN_SIGNUP_H
#define LOGIN_SIGNUP_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <database.h>

namespace Ui {
class Login_SignUp;
}

class Login_SignUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login_SignUp(DataBase *database, QWidget *parent = nullptr);
    ~Login_SignUp();


private slots :
    // Animation slot
    void animation ();

private:
    // Database
    DataBase * database;


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
    bool checkNameSignupError ();
    bool checkEmailError ();

    // Error Texts
    QString emptyError ();
    QString invalidError ();
    QString notFoundError ();


    Ui::Login_SignUp *ui;
};

#endif // LOGIN_SIGNUP_H
