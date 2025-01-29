#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <QPainter>
#include <QPainterPath>
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
    QPixmap newAvatar;
    bool changedAvatar;

public:
    explicit Settings(User* user,DataBase* dataBase,QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_avatarPB_clicked();

    void on_savePB_clicked();

    void on_DeleteAccountPB_clicked();

    void on_cancelPB_clicked();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
