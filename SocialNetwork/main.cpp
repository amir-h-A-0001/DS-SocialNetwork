#include "login_signup.h"
#include <QApplication>
#include <database.h>
#include <requests.h>
#include <suggestwidget.h>

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    DataBase database;
    Login_SignUp login_Signup(&database);
    login_Signup.show();
    //
    User user;
    QPixmap pic;
    pic.load(":/Backgrounds/Premium_Vector_Woodland_forest_landscape_with_trees_enhanced.png");
    user.setUsername("amir");
    user.setAvatar(pic);
    suggestWidget s(&user);
    //

    return a.exec();
}
