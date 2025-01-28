#include "login_signup.h"
#include <QApplication>
#include <database.h>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    DataBase database;
    Login_SignUp login_Signup(&database);
    login_Signup.show();

    return a.exec();
}
