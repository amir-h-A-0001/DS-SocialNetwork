#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include "user.h"
#include "database.h"

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

    User* user;
    DataBase* dataBase;

public:
    explicit Settings(User* user,DataBase* dataBase,QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_avatarPB_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
