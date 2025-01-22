#include "login_signup.h"
#include "ui_login_signup.h"
#include <QPropertyAnimation>
#include <QPushButton>
#include <QFrame>

Login_SignUp::Login_SignUp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login_SignUp)
{
    ui->setupUi(this);

    QFrame *frame = ui->picture;
    QPushButton *button = ui->openLoginPB;

    QPropertyAnimation *frameAnimation = new QPropertyAnimation(frame, "geometry", this);
    frameAnimation->setDuration(225);
    frameAnimation->setStartValue(frame->geometry());
    frameAnimation->setEndValue(QRect(frame->x() + 350, frame->y(), frame->width(), frame->height()));

    connect(button, SIGNAL(clicked(bool)), frameAnimation, SLOT(start()));


}

Login_SignUp::~Login_SignUp()
{
    delete ui;
}
