#include "login_signup.h"
#include <QApplication>
#include <database.h>
#include <requests.h>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    DataBase database;
    Login_SignUp login_Signup(&database);
    login_Signup.show();

    MainWindow mainw(&database, new User);
    mainw.show();

    return a.exec();
}
