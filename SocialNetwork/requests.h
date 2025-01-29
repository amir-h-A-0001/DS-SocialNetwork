#ifndef REQUESTS_H
#define REQUESTS_H

#include <QDialog>
#include <list>
#include "user.h"
#include "database.h"
#include "requestwidget.h"

namespace Ui {
class Requests;
}

class Requests : public QDialog
{
    Q_OBJECT
    DataBase* dataBase;
    User*user;

public:
    explicit Requests(User* user,DataBase* dataBase, QWidget *parent = nullptr);
    ~Requests();
public slots:
    void accept(QString username,RequestWidget* widget);
    void reject(QString username,RequestWidget* widget);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Requests *ui;
};

#endif // REQUESTS_H
