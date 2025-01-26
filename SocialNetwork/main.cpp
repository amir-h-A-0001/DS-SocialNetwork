#include "mainwindow.h"
#include "login_signup.h"
#include <QApplication>
#include <requests.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Requests r;
    r.show();

    // w.show();
    Login_SignUp s;
    // s.show();
    return a.exec();
}
