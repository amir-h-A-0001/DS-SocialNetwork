#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <database.h>
#include <postwidget.h>
#include <QHash>

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

private:
    Ui::MainWindow *ui;
    DataBase *database;
    User * user;
    User ** friends;
    int friendsSize;
    QHash <QPushButton*, User*> friendsPB;

    void setFramesShadow ();
    void setSqrollAreasLayout ();

    void setUsersFriend ();
    void setUsersInformation (User * userPage);
    void addUsersFriend ();
    void addUsersFriendPB (User * user);

    QPixmap makeCircleScalePixmap(QPixmap & pixmap, QSize & size);

private slots :
    void friendsPBCliced ();
};
#endif // MAINWINDOW_H
