#include "login_signup.h"
#include <QApplication>
#include <database.h>

int main(int argc, char *argv[]) {
#include <requests.h>

    QApplication a(argc, argv);

    DataBase database;
    Login_SignUp login_Signup(&database);
    login_Signup.show();

    MainWindow w;

    Requests r;
    r.show();

    // w.show();
    Login_SignUp s;
    // s.show();
    return a.exec();
}
