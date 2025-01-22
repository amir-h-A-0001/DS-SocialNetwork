#include "login_signup.h"
#include "ui_login_signup.h"

Login_SignUp::Login_SignUp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login_SignUp)
{
    ui->setupUi(this);
}

Login_SignUp::~Login_SignUp()
{
    delete ui;
}
