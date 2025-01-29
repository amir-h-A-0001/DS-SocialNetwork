#ifndef EDITPOST_H
#define EDITPOST_H

#include <QMainWindow>
#include "post.h"
#include "user.h"
#include "postwidget.h"
#include "database.h"
#include <list>

namespace Ui {
class EditPost;
}

class EditPost : public QMainWindow
{
    Q_OBJECT

    User* user;
    Post* post;
    PostWidget* widget;
    DataBase* dataBase;

    bool edit;

public:
    explicit EditPost(bool edit,User* user,Post* post,PostWidget* widget,DataBase* dataBase,QWidget *parent = nullptr);
    ~EditPost();

private slots:
    void on_deletePB_clicked();

    void on_cancelPB_clicked();

    void on_savePB_clicked();

signals:
    void postUpdated(QString newText);
    void postDeleted(PostWidget * postWidget);
    void newPost(Post * newPost);

private:
    Ui::EditPost *ui;
};

#endif // EDITPOST_H
