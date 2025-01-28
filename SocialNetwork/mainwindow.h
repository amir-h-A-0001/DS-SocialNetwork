#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <database.h>

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
    void setFramesShadow ();
    void fillTheLabels ();
    void setUsersFriend ();
};
#endif // MAINWINDOW_H
