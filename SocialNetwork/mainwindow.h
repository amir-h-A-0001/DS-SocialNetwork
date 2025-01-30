#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <database.h>
#include <postwidget.h>
#include <QHash>
#include <settings.h>
#include <editpost.h>
#include"suggestwidget.h"
#include "searchwidget.h"
#include "requests.h"

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
    void newPost (Post * newPost);

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
    void setUsersInformation (User * userPage);

    QPixmap makeCircleScalePixmap(QPixmap & pixmap, QSize & size);

private slots :
    void friendsPBCliced ();
    void on_settingPB_clicked();
    void openEditPost(Post* post, PostWidget* widget);
    void deletePostWidget (PostWidget * widget);


    void on_searchPB_clicked();
    void on_sideSearchPB_clicked();

    void sentRequest(QString receiver);
    void canceledRequest(QString receiver);
    void on_homePB_clicked();
    void on_sideRequestPB_clicked();
    void on_sideLogoutPB_clicked();
    void on_mainSV_currentChanged(int arg1);
};
#endif // MAINWINDOW_H
