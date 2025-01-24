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

    // Signup & Login slots
    void signupPBClicked ();
    void loginPBClicked ();

private:
    // Database
    DataBase * database;

    // Reset All LineEdits and Labels
    void resetAll ();

    void resetLoginERL ();
    void resetSignupERLB ();

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
    QString allErrorTexts (int const i);


    Ui::Login_SignUp *ui;
};

#endif // LOGIN_SIGNUP_H
