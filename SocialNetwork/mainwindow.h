#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <database.h>
#include <postwidget.h>
#include <QHash>
#include <settings.h>
#include <editpost.h>
#include "searchwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DataBase *database, User *user, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_newPostPB_clicked();

private:
    Ui::MainWindow *ui;
    DataBase *database;
    User * user;
    User ** friends;
    int friendsSize;
    QHash <QPushButton*, User*> friendsPB;

    void setFramesShadow ();
    void setFirstUiSettings ();

    void setUsersFriend ();
    void addUsersFriend ();
    void addUsersFriendPB (User * user);
    void addUsersPosts (User *userPage);
    void addUsersPostsWidgetToSA (PostWidget *post);
    void cleanUsersPostsSA ();

    QPixmap makeCircleScalePixmap(QPixmap & pixmap, QSize & size);

private slots :
    void setUsersInformation (User * userPage);
    void friendsPBCliced ();
    void on_settingPB_clicked();
    void editPostPBClicked (PostWidget * postWidget, Post * post);

    void on_searchPB_clicked();
    void on_sideSearchPB_clicked();
};
#endif // MAINWINDOW_H
