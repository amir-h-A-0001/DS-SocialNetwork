#include "editpost.h"
#include "ui_editpost.h"

EditPost::EditPost(bool edit,User* user,Post* post,PostWidget* widget,DataBase* dataBase,QWidget *parent)
    : QMainWindow(parent)
    ,user(user)
    ,post(post)
    ,widget(widget)
    ,dataBase(dataBase)
    ,edit(edit)
    , ui(new Ui::EditPost)
{
    ui->setupUi(this);

    if(edit){
        ui->textEdit->setText(post->getText());
    }
    else {

        ui->savePB->setText("Create");
        ui->deletePB->hide();
    }



}

EditPost::~EditPost()
{
    delete ui;
}

void EditPost::on_deletePB_clicked()
{
    dataBase->deletePost(user->getUsername(),post->getHashCode());
    user->removePost(*post);
    delete widget;

    // return to the mainWindow
}


void EditPost::on_cancelPB_clicked()
{
    //return to the mainWindow
}


void EditPost::on_savePB_clicked()
{
    QString newText = ui->textEdit->toPlainText();

    if(edit){
        post->setText(newText);
        widget->setText(newText);
        dataBase->editPost(user->getUsername(),post);
    }
    else {
        post = new Post;
        post->setDate(QDate::currentDate());
        post->setText(newText);
        post->setTime(QTime::currentTime());

        QString date = post->getDate().toString("yy,MM,dd");
        QString time = post->getTime().toString("HH:mm:ss");

        QString code = date + time;
        post->setHashCode(code);

        user->addPost(*post);
        dataBase->addPost(*post,user->getUsername());
    }

    // return to the mainWindow
}

