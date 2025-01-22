#include "mainwindow.h"
#include "login_signup.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    // w.show();
    Login_SignUp s;
    s.show();
    return a.exec();
}
